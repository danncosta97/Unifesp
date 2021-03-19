
##--SET foreign_key_checks = 1;


CREATE TABLE IF NOT EXISTS `player_buying_items` (
	`id` INT(11) NOT NULL AUTO_INCREMENT,
  `player_id` INT(11) NOT NULL,
  `slot` INT(11) NOT NULL,
  `item_id` INT(11) NOT NULL,
  `amount` INT(11) NOT NULL,
  `already_bought` INT(11) NOT NULL DEFAULT 0,
  `max_price_per_unit` INT(11) NOT NULL,
  `money_available` INT(11) NOT NULL,
  `created` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `ended` TIMESTAMP DEFAULT NULL,

  PRIMARY KEY (`id`)
);

ALTER TABLE `player_buying_items` ADD FOREIGN KEY (`player_id`) REFERENCES `players`(`id`);

CREATE TABLE IF NOT EXISTS `player_selling_items` (
	`id` INT(11) NOT NULL AUTO_INCREMENT,
  `player_id` INT(11) NOT NULL,
  `slot` INT(11) NOT NULL,
  `item_id` INT(11) NOT NULL,
  `amount` INT(11) NOT NULL,
  `already_sold` INT(11) NOT NULL,
  `price_per_unit` INT(11) NOT NULL,
  `money` INT(11) NOT NULL DEFAULT 0,
  `created` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `ended` TIMESTAMP DEFAULT NULL,
	`attr_important` TINYINT(4) DEFAULT 0;
  `item_attr` TEXT DEFAULT NULL,

  PRIMARY KEY (`id`)
);

ALTER TABLE `player_selling_items` ADD FOREIGN KEY (`player_id`) REFERENCES `players`(`id`);

CREATE TABLE IF NOT EXISTS `player_offers` (
	`id` INT(11) NOT NULL AUTO_INCREMENT,
  `player_id` INT(11) NOT NULL,
  `seller_id` INT(11) NOT NULL,
  `sell_transaction_id` INT(11) NOT NULL,
  `status` INT(11) NOT NULL,
  `money` INT(11) NOT NULL DEFAULT 0,

  PRIMARY KEY (`id`)
);

ALTER TABLE `player_offers` ADD FOREIGN KEY (`player_id`) REFERENCES `players`(`id`);
ALTER TABLE `player_offers` ADD FOREIGN KEY (`seller_id`) REFERENCES `players`(`id`);
ALTER TABLE `player_offers` ADD FOREIGN KEY (`sell_transaction_id`) REFERENCES `player_selling_items`(`id`);

CREATE TABLE IF NOT EXISTS `player_offers_items` (
	`offer_id` INT(11) NOT NULL,
  `slot` INT(11) NOT NULL,
  `item_id` INT(11) NOT NULL,
  `amount` INT(11) NOT NULL,
  `item_attr` TEXT DEFAULT NULL,

  PRIMARY KEY (`offer_id`, `slot`)
);

ALTER TABLE `player_offers_items` ADD FOREIGN KEY (`offer_id`) REFERENCES `player_offers`(`id`);









DELIMITER $$

## CREATE PROCEDURES !!!

$$

DROP PROCEDURE IF EXISTS `createNewOffer`;

$$

CREATE PROCEDURE `createNewOffer` (in input_player_id int, in input_transaction_id int, in input_money int, out output_offerId VARCHAR(22), out output_error TEXT)

bye: begin

  declare r_seller_id int;
  declare r_player_money int;

    #Verify if transaction is still on !

  SELECT `player_id` FROM `player_selling_items` WHERE `id` = input_transaction_id INTO r_seller_id;

  if r_seller_id IS NULL then
		SET output_error = "Sorry, the item you are trying to make an offer was already sold.";
		LEAVE bye;
	end if;

	#Verify if there is any offer available from this player in this item.

	if exists(SELECT `id` FROM `player_offers` WHERE `player_id` = input_player_id AND `seller_id` = r_seller_id AND `sell_transaction_id` = input_transaction_id) then
		SET output_error = "Sorry, you already have an oppened offer on this item.";
		LEAVE bye;
  end if;

	SELECT `balance` FROM `players` WHERE `id` = input_player_id INTO r_player_money;

	if r_player_money < input_money then
		SET output_error = "Not enough money to complete the offer.";
		LEAVE bye;
	end if;

  UPDATE `players` SET `balance` = (r_player_money - input_money) WHERE `id` = input_player_id;

  INSERT INTO `player_offers` (`player_id`, `seller_id`, `sell_transaction_id`, `status`, `money`) VALUES (input_player_id, r_seller_id, input_transaction_id, 0, input_money);

  SELECT `id` FROM `player_offers` WHERE `id` = LAST_INSERT_ID() INTO output_offerId;

  SET output_error = NULL;

end

$$

DROP PROCEDURE IF EXISTS `createAutoBuyOffer`;

$$

CREATE PROCEDURE `createAutoBuyOffer`(in input_slot int, in input_player_id int, in input_item_id int, in input_amount int, in input_max_price_per_unit int, out output_id int, out output_msg_error TEXT)

bye: begin

	if exists(SELECT id FROM `player_buying_items` WHERE `slot` = input_slot AND `player_id` = input_player_id) then
		SET output_id = 0;
		SET output_msg_error = "Sorry, this slot is already occupied.";
    LEAVE bye;
	end if;

  if exists(SELECT id FROM `player_buying_items` WHERE `item_id` = input_item_id AND `player_id` = input_player_id) then
	  SET output_id = 0;
		SET output_msg_error = "Sorry, you are already attempting to buy this item.";
    LEAVE bye;
	end if;

  INSERT INTO `player_buying_items` (`player_id`, `slot`, `item_id`, `amount`, `max_price_per_unit`, `money_available`) VALUES (input_player_id, input_slot, input_item_id, input_amount, input_max_price_per_unit, (input_amount*input_max_price_per_unit));

  SET output_id = LAST_INSERT_ID();
  SET output_msg_error = NULL;

end

$$

DROP PROCEDURE IF EXISTS `createAutoSellOffer`;

$$

CREATE PROCEDURE `createAutoSellOffer` (in input_slot int, in input_player_id int, in input_item_id int, in input_amount int, in input_price_per_unit int, in input_attr_important int, in input_item_attr TEXT, out output_id int, out output_msg_error TEXT)
bye: begin

	if exists(SELECT id FROM `player_selling_items` WHERE `slot` = input_slot AND `player_id` = input_player_id) then
	  SET output_id = 0;
		SET output_msg_error = "Sorry, this slot is already occupied.";
  end if;

  if exists(SELECT id FROM `player_selling_items` WHERE `item_id` = input_item_id AND `player_id` = input_player_id) then
    SET output_id = 0;
		SET output_msg_error = "Sorry, you are already attempting to sell this item.";
    LEAVE bye;
	end if;

	INSERT INTO `player_selling_items` (`player_id`, `slot`, `item_id`, `amount`, `price_per_unit`, `attr_important`, `item_attr`) VALUES (input_player_id, input_slot, input_item_id, input_amount, input_price_per_unit, input_attr_important, input_item_attr);

	SET output_id = LAST_INSERT_ID();
  SET output_msg_error = NULL;

end


## OPERATION PROCEDURES


$$

DROP PROCEDURE IF EXISTS `buyMarketItemFromPlayer`;

$$

CREATE PROCEDURE `buyMarketItemFromPlayer` (in input_itemID int, in input_amount int, in input_price_per_unit int, in input_sellerID int, out r_id int, out r_price int, out r_attr TEXT)

begin

	declare itemID int;
	declare total_amount int;
	declare r_price_per_unit int;
	declare r_amount int;
	declare r_already_sold int;
	declare r_total_amount int;
	declare r_money int;
	declare r_attr int;

	SELECT id, price_per_unit, amount, already_sold, money, item_attr FROM `player_selling_items`
		WHERE `player_id` = input_sellerID AND `item_id` = input_itemID AND (amount-already_sold) >= input_amount AND `price_per_unit` <= input_price_per_unit ORDER BY `price_per_unit` ASC LIMIT 1
			INTO r_id, r_price_per_unit, r_amount, r_already_sold, r_money, r_attr;

  SET r_total_amount = r_amount - r_already_sold;

  SET r_price = r_price_per_unit * input_amount;

  if (r_already_sold+input_amount = r_amount) then
		UPDATE `player_selling_items` SET `already_sold` = (r_already_sold+input_amount), `money` = (r_money + r_price), `ended` = CURRENT_TIMESTAMP WHERE `id` = r_id;
  else
		UPDATE `player_selling_items` SET `already_sold` = (r_already_sold+input_amount), `money` = (r_money + r_price) WHERE `id` = r_id;
  end if;

end

$$

CALL `buyMarketItemFromPlayer`(2394, 50, 300, 2, @r1, @r2, @r3);

$$

SELECT @r1, @r2, @r3;

$$

DROP PROCEDURE IF EXISTS `autoBuyMarketItem`;

$$

CREATE PROCEDURE `autoBuyMarketItem` (in input_id int)

begin

	declare r_id int;
	declare r_amount int;
	declare r_already_sold int;
	declare r_amount_available int;
  declare r_price_per_unit int;
	declare r_money int;

	declare amount_bought int;
	declare price int;

  declare b_itemID int;
  declare b_amount int;
  declare b_already_bought_amount int;
  declare b_max_price_per_unit int;
  declare b_money int;

  declare b_amount_to_buy int;

	SELECT item_id, amount, already_bought, max_price_per_unit, money_available FROM `player_buying_items`
	WHERE `id` = input_id INTO b_itemID, b_amount, b_already_bought_amount, b_max_price_per_unit, b_money;

  SET b_amount_to_buy = amount - b_already_bought_amount;

  if b_amount_to_buy > 0 then

		SELECT id, amount, already_sold, price_per_unit, money FROM `player_selling_items`
		WHERE `item_id` = b_itemID AND (amount-already_sold) > 0 AND `price_per_unit` <= b_max_price_per_unit ORDER BY `price_per_unit` ASC LIMIT 1
		INTO r_id, r_amount, r_already_sold, r_price_per_unit, r_money;

		SET r_amount_available = r_amount - r_already_sold;

		if r_amount_available < b_amount_to_buy then
			SET amount_bought = r_amount_available;
			SET price = amount_bought*r_price_per_unit;

			UPDATE `player_selling_items` SET `already_sold` = r_amount, `money` = (r_money + price), `ended` = CURRENT_TIMESTAMP WHERE `id` = r_id;
		else
			SET amount_bought = r_amount_available - b_amount_to_buy;
			SET price = amount_bought*r_price_per_unit;

			UPDATE `player_selling_items` SET `already_sold` = (r_already_sold + amount_bought), `money` = (r_money + price) WHERE `id` = r_id;

		end if;

		UPDATE `player_buying_items` SET `already_bought` = (b_already_bought_amount + amount_bought), `money_available` = (b_money-price) WHERE `id` = input_id;

  end if;

end

$$

DROP PROCEDURE IF EXISTS `getBuySlotStatus`;

$$

CREATE PROCEDURE `getBuySlotStatus` (in input_player_id int, in input_slot_id int, out output_item_id int, out output_amount int, out output_amount_bought int, out output_created timestamp, out output_ended timestamp, out output_percent int)

begin
	declare i int;

  SELECT item_id, amount, amount_bought, created, ended FROM `player_buying_items`
	WHERE `player_id` = input_player_id AND `slot` = input_slot_id
	INTO output_item_id, output_amount, output_amount_bought, output_created, output_ended;

	SET output_percent = ((amount_bought/amount)*100);

end

$$

DROP PROCEDURE IF EXISTS `getSellSlotStatus`;

$$

CREATE PROCEDURE `getSellSlotStatus` (in input_player_id int, in input_slot_id int, out output_item_id int, out output_amount int, out output_amount_bought int, out output_created timestamp, out output_ended timestamp, out output_percent int)

begin
	declare i int;

  SELECT item_id, amount, amount_bought, created, ended FROM `player_buying_items` WHERE `player_id` = input_player_id AND `slot` = input_slot_id INTO output_item_id, output_amount, output_amount_bought, output_created, output_ended;

  SET output_percent = ((amount_bought/amount)*100);

end

$$

DELIMITER ;
