CREATE TABLE IF NOT EXISTS `cliente` (
  `idcliente` INT NOT NULL AUTO_INCREMENT,
  `passw` VARCHAR(50) NOT NULL,
  `name` VARCHAR(45) NOT NULL,
  `surname` VARCHAR(45) NOT NULL,
  `email` VARCHAR(50) NOT NULL,
  `gender` INT NOT NULL,
  `cpf` VARCHAR(11) NOT NULL,
  `nascimento` DATE NOT NULL,
  `tel1` VARCHAR(11) NOT NULL,
  `tel2` VARCHAR(11),
  `device_id` varchar(50),
  PRIMARY KEY (`idcliente`)
  )
ENGINE = InnoDB;

--
-- Esquema de hieraraquia via top id
--
CREATE TABLE IF NOT EXISTS `tiposTickets` (
  `idTiposTickets` INT NOT NULL AUTO_INCREMENT,
  `top_id` INT,
  PRIMARY KEY (`idTiposTickets`),
  FOREIGN KEY (top_id) REFERENCES tiposTickets(idTiposTickets)
  )
ENGINE = InnoDB;

-- -----------------------------------------------------
-- Tabela `empresa`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `empresa` (
	`idempresa` INT NOT NULL AUTO_INCREMENT,
	`name` VARCHAR(50) NOT NULL,
    `passw` varchar(50) NOT NULL,
	`razao_social` VARCHAR(45) NOT NULL,
	`email` VARCHAR(50) NOT NULL,
	`cnpj` VARCHAR(15) NOT NULL,
	`dataRegistro` DATE NOT NULL,
	`tel1` VARCHAR(11) NOT NULL,
	`tel2` VARCHAR(11) NULL,
	`tipo_ticket_empresa` INT NOT NULL,
    `mainticket` INT NOT NULL,
    `device_id` varchar(50),
	PRIMARY KEY (`idempresa`),
    FOREIGN KEY (mainticket) REFERENCES tiposTickets(idTiposTickets)
  )  
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Tabela `ticket`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `ticket` (
	`idticket` INT NOT NULL AUTO_INCREMENT,
	`cliente_id` int NOT NULL,
	`empresa_id` int NULL,
	`data` DATE NOT NULL,
	`titulo` VARCHAR(45) NOT NULL,
	`descricao` VARCHAR(300) NOT NULL,
	`tipo` INT NOT NULL,
	PRIMARY KEY (`idticket`),
	FOREIGN KEY (cliente_id) REFERENCES cliente(idcliente),
    FOREIGN KEY (empresa_id) REFERENCES empresa(idempresa),
    FOREIGN KEY (tipo) REFERENCES tiposTickets(idTiposTickets)
  )
ENGINE = InnoDB;
-- DROP TABLE ticket;


--
-- Tabela localizacao
--
CREATE TABLE IF NOT EXISTS `localizacao`(
	`id_loc` INT NOT NULL AUTO_INCREMENT,
    `cep` VARCHAR(8) NOT NULL,
	`tipo_end` VARCHAR(20) NOT NULL,
	`nome_end` VARCHAR(45) NOT NULL,
	`numero_end` VARCHAR(45) NOT NULL,
	`complemento_end` VARCHAR(45) NULL,
	`estado_end` VARCHAR(45) NOT NULL,
	`cidade_end` VARCHAR(45) NOT NULL,
	`bairro_end` VARCHAR(45) NOT NULL,
    `cliente_id` int NULL,
    `empresa_id` int NULL,
    PRIMARY KEY (id_loc),
    FOREIGN KEY (cliente_id) REFERENCES cliente(idcliente),
    FOREIGN KEY (empresa_id) REFERENCES empresa(idempresa)
)
ENGINE = InnoDB;
DROP TABLE localizacao;


DELIMITER $$

-- PROCEDURES

$$

DROP PROCEDURE IF EXISTS `registerCliente`;

$$

CREATE PROCEDURE `registerCliente` (in input_cliente_name varchar(45),in input_cliente_passw varchar(50), in input_cliente_surname varchar(45), 
in input_cliente_email varchar(50), in input_cliente_gender int, in input_cliente_cpf varchar(11),
in input_cliente_tel1 varchar(11), in input_cliente_tel2 varchar(11), input_cliente_nascimento date,
 out output_error TEXT)

bye: begin

	declare temp varchar(50);

    #Verify email

	SELECT `idcliente` FROM `cliente` WHERE `email` = input_cliente_email INTO temp;

	if temp IS NOT NULL then
		SET output_error = "Este email já está cadastrado!";
		LEAVE bye;
	end if;

	#Verify cpf
    SELECT `idcliente` FROM `cliente` WHERE `cpf` = input_cliente_cpf INTO temp;

	if temp IS NOT NULL then
		SET output_error = "Este CPF já está cadastrado!";
		LEAVE bye;
	end if;

	INSERT INTO 
    `cliente` (`passw`, `name`, `surname`, `email`, `gender`, `cpf`, `nascimento`,`tel1`,`tel2`)
    VALUES (input_cliente_passw, input_cliente_name, input_cliente_surname, input_cliente_email, input_cliente_gender,
    input_cliente_cpf,input_cliente_nascimento, input_cliente_tel1, input_cliente_tel2);

	SET output_error = NULL;

end


$$

DROP PROCEDURE IF EXISTS `registerEmpresa`;

$$



CREATE PROCEDURE `registerEmpresa` (in input_empresa_name varchar(50), in input_empresa_passw VARCHAR(50),
	in input_empresa_razao_social VARCHAR(45), in input_empresa_email VARCHAR(50),
	in input_empresa_cnpj VARCHAR(15), in input_empresa_dataRegistro DATE, in input_empresa_tel1 VARCHAR(11),
	in input_empresa_tel2 VARCHAR(11), in input_empresa_tipo_ticket_empresa INT, in input_empresa_mainticket INT,
    out output_error TEXT)

bye: begin

	declare temp varchar(50);

    #Verify email

	SELECT `idempresa` FROM `empresa` WHERE `email` = input_empresa_email INTO temp;

	if temp IS NOT NULL then
		SET output_error = "Este email já está cadastrado!";
		LEAVE bye;
	end if;

	#Verify cnpj
    SELECT `idempresa` FROM `empresa` WHERE `cnpj` = input_empresa_cnpj INTO temp;

	if temp IS NOT NULL then
		SET output_error = "Este CNPJ já está cadastrado!";
		LEAVE bye;
	end if;

	INSERT INTO 
    `empresa` (`passw`, `name`, `razao_social`, `email`, `cnpj`, `dataRegistro`, `tel1`,`tel2`,`tipo_ticket_empresa`,`mainticket`)
    VALUES (input_empresa_passw, input_empresa_name, input_empresa_razao_social,input_empresa_email,input_empresa_cnpj,
	input_empresa_dataRegistro,	input_empresa_tel1,	input_empresa_tel2,	input_empresa_tipo_ticket_empresa, input_empresa_mainticket);

	SET output_error = NULL;

end

$$

DROP PROCEDURE IF EXISTS `login`;

$$

CREATE PROCEDURE `login` (in input_email varchar(50),in input_passw varchar(50), in input_cliente_cpf varchar(11),
	in input_empresa_cnpj VARCHAR(15), in input_device_id VARCHAR(50), 
	out output_error TEXT)

bye: begin

	declare temp varchar(50);
	SET temp = null;
    
    #loga via id,email,cpf
	SELECT `device_id` FROM `cliente` WHERE `input_device_id` = input_device_id INTO temp;
    if temp IS NOT NULL then
		SET output_error = "logado";
        LEAVE bye;
    else
    SELECT `passw` FROM `cliente` WHERE `email` = input_email INTO temp;
	if temp IS NOT NULL then
		if temp = input_passw then
			SET output_error = "logado";
			LEAVE bye;
		end if;
	else
    SELECT `passw` FROM `cliente` WHERE `cpf` = input_cliente_cpf INTO temp;
	if temp IS NOT NULL then
		if temp = input_passw then
			SET output_error = "logado";
			LEAVE bye;
		end if;
	end if;
    end if;
    end if;

    #loga via id,email,cnpj
    SELECT `device_id` FROM `empresa` WHERE `input_device_id` = input_device_id INTO temp;
    if temp IS NOT NULL then
			SET output_error = "logado";
            LEAVE bye;
    else 
    SELECT `passw` FROM `empresa` WHERE `email` = input_email INTO temp;
	if temp IS NOT NULL then
		if temp = input_passw then
			SET output_error = "logado";
			LEAVE bye;
		end if;
	else
    SELECT `passw` FROM `empresa` WHERE `cnpj` = input_cnpj INTO temp;
	if temp IS NOT NULL then
		if temp = input_passw then
			SET output_error = "logado";
			LEAVE bye;
		end if;
	end if;
    end if; 
	end if;
    
	SET output_error = "Usuario nao registrado";

end

$$
