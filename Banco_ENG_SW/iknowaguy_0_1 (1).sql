

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