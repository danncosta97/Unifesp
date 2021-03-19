-- phpMyAdmin SQL Dump
-- version 4.6.6deb5
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: 19-Out-2018 às 21:16
-- Versão do servidor: 5.7.22-0ubuntu0.17.10.1
-- PHP Version: 7.1.17-0ubuntu0.17.10.1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `iknowaguy_0_1`
--

DELIMITER $$
--
-- Procedures
--
CREATE DEFINER=`root`@`localhost` PROCEDURE `getTicket` (IN `input_id_cliente` INT(11), OUT `output_error` TEXT)  bye: begin
    declare output_text TEXT;
    
    SELECT * FROM `ticket` WHERE `cliente_id` = input_id_cliente;
    
	SET output_error = output_text; end$$

CREATE DEFINER=`root`@`localhost` PROCEDURE `login` (IN `input_input` VARCHAR(50), IN `input_passwd` VARCHAR(50), IN `input_device_id` VARCHAR(50), OUT `output_error` TEXT)  bye: begin

	declare temp varchar(50);
	SET temp = null;
    
    	SELECT `device_id` FROM `cliente` WHERE `device_id` = input_device_id INTO temp;
    if temp IS NOT NULL then
		SET output_error = "1002";
        LEAVE bye;
    else
		SELECT `passwd` FROM `cliente` WHERE `email` = input_input INTO temp;
		if temp IS NOT NULL then
			if temp = input_passwd then
				SET output_error = "1002";
				LEAVE bye;
			else
				SET output_error = "10104";
				LEAVE bye;
            end if;
            
		else
			SELECT `passwd` FROM `cliente` WHERE `cpf` = input_input INTO temp;
			if temp IS NOT NULL then
				if temp = input_passwd then
					SET output_error = "1002";
					LEAVE bye;
				else
					SET output_error = "10104";
					LEAVE bye;
				end if;
			end if;
		end if;
    end if;

        SELECT `device_id` FROM `empresa` WHERE `device_id` = input_device_id INTO temp;
    if temp IS NOT NULL then
		SET output_error = "1002";
		LEAVE bye;
    else 
		SELECT `passwd` FROM `empresa` WHERE `email` = input_input INTO temp;
		if temp IS NOT NULL then
			if temp = input_passwd then
				SET output_error = "1002";
				LEAVE bye;
			else
				SET output_error = "10104";
				LEAVE bye;
			end if;
		else
			SELECT `passwd` FROM `empresa` WHERE `cnpj` = input_input INTO temp;
			if temp IS NOT NULL then
				if temp = input_passwd then
					SET output_error = "1002";
					LEAVE bye;
				else
					SET output_error = "10104";
					LEAVE bye;
				end if;
			end if;
		end if; 
	end if;
    
	SET output_error = "10103";
	
end$$



CREATE DEFINER=`root`@`localhost` PROCEDURE `getClienteId` (IN `input_email` VARCHAR(50), IN `input_device_id` VARCHAR(50), OUT `output_id` INT(11))  bye: begin
	declare temp VARCHAR(50);
    SET temp = input_device_id;
    if temp IS NULL then
		SET temp = input_email;
    end if;
    
    SELECT `id_cliente` FROM `cliente` WHERE `email` = input_email INTO output_id;
    
end$$

CREATE DEFINER=`root`@`localhost` PROCEDURE `getClienteInfo` (IN `input_id_cliente` INT(11), OUT `output_cpf` VARCHAR(45), OUT `output_name` VARCHAR(45),
 OUT `output_surname` VARCHAR(45), OUT `output_birth` DATE, OUT `output_email` VARCHAR(50), OUT `output_mtel` VARCHAR(11), OUT `output_stel` VARCHAR(45),
 OUT `output_registerdate` TIMESTAMP)  bye: begin

	declare temp varchar(50);
	SET temp = null;
    
	SELECT `cpf` FROM `cliente` WHERE `id_cliente` = input_id_cliente INTO output_cpf;
    SELECT `name` FROM `cliente` WHERE `id_cliente` = input_id_cliente INTO output_name;
    SELECT `surname` FROM `cliente` WHERE `id_cliente` = input_id_cliente INTO output_surname;
    SELECT `birth` FROM `cliente` WHERE `id_cliente` = input_id_cliente INTO output_birth;
    SELECT `email` FROM `cliente` WHERE `id_cliente` = input_id_cliente INTO output_email;
    SELECT `main_tel` FROM `cliente` WHERE `id_cliente` = input_id_cliente INTO output_mtel;
    SELECT `secondary_tel` FROM `cliente` WHERE `id_cliente` = input_id_cliente INTO output_stel;
	SELECT `registered_since` FROM `cliente` WHERE `id_cliente` = input_id_cliente INTO output_registerdate;
		
end$$

CREATE DEFINER=`root`@`localhost` PROCEDURE `registerCliente` (IN `input_cliente_name` VARCHAR(45), IN `input_cliente_passwd` VARCHAR(50), IN `input_cliente_surname` VARCHAR(45), IN `input_cliente_email` VARCHAR(50), IN `input_cliente_gender` INT, IN `input_cliente_cpf` VARCHAR(11), IN `input_cliente_main_tel` VARCHAR(11), IN `input_cliente_secondary_tel` VARCHAR(11), IN `input_cliente_birth` DATE, OUT `output_error` TEXT)  bye: begin

	declare temp varchar(50);

    
	SELECT `id_cliente` FROM `cliente` WHERE `email` = input_cliente_email INTO temp;

	if temp IS NOT NULL then
		SET output_error = "10101";
		LEAVE bye;
	end if;

	    SELECT `id_cliente` FROM `cliente` WHERE `cpf` = input_cliente_cpf INTO temp;

	if temp IS NOT NULL then
		SET output_error = "10102";
		LEAVE bye;
	end if;

	INSERT INTO 
    `cliente` (`passwd`, `name`, `surname`, `email`, `gender`, `cpf`, `birth`,`main_tel`,`secondary_tel`)
    VALUES (input_cliente_passwd, input_cliente_name, input_cliente_surname, input_cliente_email, input_cliente_gender,
    input_cliente_cpf,input_cliente_birth, input_cliente_main_tel, input_cliente_secondary_tel);

	SET output_error = "1001";

end$$

CREATE DEFINER=`root`@`localhost` PROCEDURE `registerTicket` (IN `input_cliente_id` INT(11), IN `input_ticket_title` VARCHAR(45), IN `input_ticket_desc` VARCHAR(300), IN `input_ticket_type` INT, OUT `output_error` TEXT)  bye: begin
	declare dia varchar(50);
    
    IF (input_ticket_title) IS NULL THEN
		SET output_error = "1001";        leave bye;
    END IF;
    
	IF (input_ticket_desc) IS NULL THEN
		SET output_error = "1002";        leave bye;
    END IF;
    
	IF (input_ticket_type) IS NULL THEN
		SET output_error = "1003";        leave bye;
    END IF;
    
	SELECT GETDATE() INTO dia;
	
	INSERT INTO 
    `ticket` (`cliente_id`, `data`, `title`, `desc`, `ticket_type`)
    VALUES (input_cliente_id, dia, input_ticket_title, input_ticket_desc,input_ticket_type);

	SET output_error = "1000"; 
end$$

CREATE DEFINER=`root`@`localhost` PROCEDURE `returnAbleCompany` (IN `input_ticket_id` INT(11), OUT `output_error` TEXT)  bye: begin
    
    declare output_text TEXT;
    declare temp INT;
    
    SELECT `ticket_type` from `ticket` where `id_ticket` = input_ticket_id INTO temp;
    
    
	SELECT `parent_type_id` FROM `ticket_types` where `type_id = temp` INTO temp;
    WHILE (SELECT `parent_type_id` FROM `ticket_types` where `type_id` = temp) IS NULL DO
		SELECT `parent_type_id` FROM `ticket_types` where `type_id` = temp INTO temp;
    END WHILE;
        
	SELECT `id_empresa` FROM `empresa` where `main_ticket_types` = temp INTO output_text;
    
	SET output_error = output_text; 
end$$

CREATE DEFINER=`root`@`localhost` PROCEDURE `setCompanyToTicket` (IN `input_ticket_id` INT(11), IN `input_empresa_id` INT(11), OUT `output_error` TEXT)  bye: begin
    declare output_text INT;
    
    UPDATE `ticket` SET `empresa_id` = input_empresa_id WHERE `id_ticket` = input_ticket_id;
    
	SET output_error = 1000; end$$

DELIMITER ;

-- --------------------------------------------------------

--
-- Estrutura da tabela `cliente`
--

CREATE TABLE `cliente` (
  `id_cliente` int(11) NOT NULL,
  `passwd` varchar(50) NOT NULL,
  `name` varchar(45) NOT NULL,
  `surname` varchar(45) NOT NULL,
  `email` varchar(50) NOT NULL,
  `gender` int(11) NOT NULL,
  `cpf` varchar(11) NOT NULL,
  `birth` date NOT NULL,
  `registered_since` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `main_tel` varchar(11) NOT NULL,
  `secondary_tel` varchar(11) DEFAULT NULL,
  `device_id` varchar(50) DEFAULT NULL,
  `profile_img` longblob
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Extraindo dados da tabela `cliente`
--


-- --------------------------------------------------------

--
-- Estrutura da tabela `empresa`
--

CREATE TABLE `empresa` (
  `id_empresa` int(11) NOT NULL,
  `nome` varchar(50) NOT NULL,
  `passwd` varchar(50) NOT NULL,
  `razao_social` varchar(45) NOT NULL,
  `email` varchar(50) NOT NULL,
  `cnpj` varchar(15) NOT NULL,
  `registered_since` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `main_tel` varchar(11) NOT NULL,
  `secondary_tel` varchar(11) DEFAULT NULL,
  `main_ticket_types` int(11) NOT NULL,
  `device_id` varchar(50) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Estrutura da tabela `localizacao`
--

CREATE TABLE `localizacao` (
  `id_loc` int(11) NOT NULL,
  `cep` varchar(8) NOT NULL,
  `tipo_end` varchar(20) NOT NULL,
  `nome_end` varchar(45) NOT NULL,
  `numero_end` varchar(45) NOT NULL,
  `complemento_end` varchar(45) DEFAULT NULL,
  `estado_end` varchar(45) NOT NULL,
  `cidade_end` varchar(45) NOT NULL,
  `bairro_end` varchar(45) NOT NULL,
  `id_cliente` int(11) DEFAULT NULL,
  `id_empresa` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Estrutura da tabela `ticket`
--

CREATE TABLE `ticket` (
  `id_ticket` int(11) NOT NULL,
  `cliente_id` int(11) NOT NULL,
  `empresa_id` int(11) DEFAULT NULL,
  `data` date NOT NULL,
  `title` varchar(45) NOT NULL,
  `desc` varchar(300) NOT NULL,
  `ticket_type` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Estrutura da tabela `ticket_types`
--

CREATE TABLE `ticket_types` (
  `type_id` int(11) NOT NULL,
  `parent_type_id` int(11) DEFAULT NULL,
  `type_name` varchar(30) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Extraindo dados da tabela `ticket_types`
--

INSERT INTO `ticket_types` (`type_id`, `parent_type_id`, `type_name`) VALUES
(1, NULL, 'Eletrônicos'),
(2, NULL, 'Veículos'),
(3, NULL, 'Beleza e Cuidado Pessoal'),
(4, NULL, 'Casa e Eletrodomésticos'),
(5, NULL, 'Brinquedos'),
(6, NULL, 'Moda'),
(7, NULL, 'Instrumentos Musicais'),
(8, NULL, 'Serviços Domésticos'),
(9, NULL, 'Jóias e Relógios'),
(10, NULL, 'Outros'),
(11, 1, 'Celulares e Telefones'),
(12, 1, 'Informática'),
(13, 1, 'Câmeras e acessórios'),
(14, 1, 'Áudio e Vídeo'),
(15, 1, 'Games'),
(16, 2, 'Carros, Vans e Utilitários'),
(17, 2, 'Motos'),
(18, 2, 'Barcos'),
(19, 2, 'Ônibus'),
(20, 3, 'Eletrodomésticos de Beleza'),
(21, 3, 'Cuidados de mãos'),
(22, 3, 'Cuidados com a pele'),
(23, 3, 'Cuidados com o cabelo'),
(24, 4, 'Eletrodomésticos'),
(25, 4, 'Decoração'),
(26, 4, 'Iluminação'),
(27, 5, 'Bonecos e Figuras de ação'),
(28, 5, 'Jogos'),
(29, 6, 'Calças'),
(30, 6, 'Vestidos'),
(31, 6, 'Camisas e Ternos'),
(32, 7, 'Instrumentos de Corda'),
(33, 7, 'Instrumentos de Percurssão'),
(34, 7, 'Instrumentos de Sopro'),
(36, 7, 'Outros tipos de Instrumentos'),
(37, 8, 'Encanamento'),
(38, 8, 'Elétrico'),
(39, 8, 'Pintura'),
(40, 8, 'Piso'),
(41, 8, 'Outros'),
(42, 9, 'Relógios'),
(43, 9, 'Jóias');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `cliente`
--
ALTER TABLE `cliente`
  ADD PRIMARY KEY (`id_cliente`);

--
-- Indexes for table `empresa`
--
ALTER TABLE `empresa`
  ADD PRIMARY KEY (`id_empresa`),
  ADD KEY `main_ticket_types` (`main_ticket_types`);

--
-- Indexes for table `localizacao`
--
ALTER TABLE `localizacao`
  ADD PRIMARY KEY (`id_loc`),
  ADD KEY `id_cliente` (`id_cliente`),
  ADD KEY `id_empresa` (`id_empresa`);

--
-- Indexes for table `ticket`
--
ALTER TABLE `ticket`
  ADD PRIMARY KEY (`id_ticket`),
  ADD KEY `cliente_id` (`cliente_id`),
  ADD KEY `empresa_id` (`empresa_id`),
  ADD KEY `ticket_type` (`ticket_type`);

--
-- Indexes for table `ticket_types`
--
ALTER TABLE `ticket_types`
  ADD PRIMARY KEY (`type_id`),
  ADD KEY `parent_type_id` (`parent_type_id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `cliente`
--
ALTER TABLE `cliente`
  MODIFY `id_cliente` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=15;
--
-- AUTO_INCREMENT for table `empresa`
--
ALTER TABLE `empresa`
  MODIFY `id_empresa` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `localizacao`
--
ALTER TABLE `localizacao`
  MODIFY `id_loc` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `ticket`
--
ALTER TABLE `ticket`
  MODIFY `id_ticket` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `ticket_types`
--
ALTER TABLE `ticket_types`
  MODIFY `type_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=44;
--
-- Constraints for dumped tables
--

--
-- Limitadores para a tabela `empresa`
--
ALTER TABLE `empresa`
  ADD CONSTRAINT `empresa_ibfk_1` FOREIGN KEY (`main_ticket_types`) REFERENCES `ticket_types` (`type_id`);

--
-- Limitadores para a tabela `localizacao`
--
ALTER TABLE `localizacao`
  ADD CONSTRAINT `localizacao_ibfk_1` FOREIGN KEY (`id_cliente`) REFERENCES `cliente` (`id_cliente`),
  ADD CONSTRAINT `localizacao_ibfk_2` FOREIGN KEY (`id_empresa`) REFERENCES `empresa` (`id_empresa`);

--
-- Limitadores para a tabela `ticket`
--
ALTER TABLE `ticket`
  ADD CONSTRAINT `ticket_ibfk_1` FOREIGN KEY (`cliente_id`) REFERENCES `cliente` (`id_cliente`),
  ADD CONSTRAINT `ticket_ibfk_2` FOREIGN KEY (`empresa_id`) REFERENCES `empresa` (`id_empresa`),
  ADD CONSTRAINT `ticket_ibfk_3` FOREIGN KEY (`ticket_type`) REFERENCES `ticket_types` (`type_id`);

--
-- Limitadores para a tabela `ticket_types`
--
ALTER TABLE `ticket_types`
  ADD CONSTRAINT `ticket_types_ibfk_1` FOREIGN KEY (`parent_type_id`) REFERENCES `ticket_types` (`type_id`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
