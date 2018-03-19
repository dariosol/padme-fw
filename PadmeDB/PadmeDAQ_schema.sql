-- MySQL Script generated by MySQL Workbench
-- 03/19/18 17:40:23
-- Model: New Model    Version: 1.0
-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Schema PadmeDAQ
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `PadmeDAQ` ;

-- -----------------------------------------------------
-- Schema PadmeDAQ
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `PadmeDAQ` DEFAULT CHARACTER SET utf8 ;
USE `PadmeDAQ` ;

-- -----------------------------------------------------
-- Table `PadmeDAQ`.`run`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `PadmeDAQ`.`run` (
  `number` INT NOT NULL,
  `type` VARCHAR(45) NOT NULL,
  `status` INT NOT NULL,
  `time_init` DATETIME NULL,
  `time_start` DATETIME NULL,
  `time_stop` DATETIME NULL,
  `total_events` INT UNSIGNED NULL,
  `user` VARCHAR(1024) NULL,
  `comment_start` VARCHAR(10240) NULL,
  `comment_end` VARCHAR(10240) NULL,
  PRIMARY KEY (`number`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `PadmeDAQ`.`optical_link`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `PadmeDAQ`.`optical_link` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `node_id` INT UNSIGNED NOT NULL,
  `controller_id` INT UNSIGNED NOT NULL,
  `channel_id` INT UNSIGNED NOT NULL,
  `slot_id` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `PadmeDAQ`.`daq_process`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `PadmeDAQ`.`daq_process` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `run_number` INT NOT NULL,
  `optical_link_id` INT NOT NULL,
  `status` INT NOT NULL,
  `time_start` DATETIME NULL,
  `time_stop` DATETIME NULL,
  `n_daq_files` INT UNSIGNED NULL,
  `total_events` INT UNSIGNED NULL,
  `total_size` BIGINT UNSIGNED NULL,
  PRIMARY KEY (`id`),
  INDEX `fk_daq_process_run1_idx` (`run_number` ASC),
  INDEX `fk_daq_process_optical_link1_idx` (`optical_link_id` ASC),
  CONSTRAINT `fk_daq_process_run1`
    FOREIGN KEY (`run_number`)
    REFERENCES `PadmeDAQ`.`run` (`number`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_daq_process_optical_link1`
    FOREIGN KEY (`optical_link_id`)
    REFERENCES `PadmeDAQ`.`optical_link` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `PadmeDAQ`.`board_type`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `PadmeDAQ`.`board_type` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `type` VARCHAR(45) NOT NULL,
  `manufacturer` VARCHAR(45) NOT NULL,
  `model` VARCHAR(45) NOT NULL,
  `n_channels` INT UNSIGNED NULL,
  PRIMARY KEY (`id`),
  UNIQUE INDEX `manu_model` (`manufacturer` ASC, `model` ASC))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `PadmeDAQ`.`board`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `PadmeDAQ`.`board` (
  `id` INT NOT NULL,
  `serial_number` VARCHAR(45) NOT NULL,
  `board_type_id` INT NOT NULL,
  PRIMARY KEY (`id`),
  INDEX `fk_board_board_type1_idx` (`board_type_id` ASC),
  UNIQUE INDEX `u_btsn` (`serial_number` ASC, `board_type_id` ASC),
  CONSTRAINT `fk_board_board_type1`
    FOREIGN KEY (`board_type_id`)
    REFERENCES `PadmeDAQ`.`board_type` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `PadmeDAQ`.`config_para_name`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `PadmeDAQ`.`config_para_name` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(128) NULL,
  UNIQUE INDEX `name_UNIQUE` (`name` ASC),
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `PadmeDAQ`.`daq_proc_config_para`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `PadmeDAQ`.`daq_proc_config_para` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `daq_process_id` INT NOT NULL,
  `config_para_name_id` INT NOT NULL,
  `value` VARCHAR(1024) NOT NULL,
  PRIMARY KEY (`id`),
  INDEX `fk_daq_proc_config_para_config_para_name1_idx` (`config_para_name_id` ASC),
  INDEX `fk_daq_proc_config_para_process1_idx` (`daq_process_id` ASC),
  CONSTRAINT `fk_daq_proc_config_para_config_para_name1`
    FOREIGN KEY (`config_para_name_id`)
    REFERENCES `PadmeDAQ`.`config_para_name` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_daq_proc_config_para_process1`
    FOREIGN KEY (`daq_process_id`)
    REFERENCES `PadmeDAQ`.`daq_process` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `PadmeDAQ`.`run_config_para`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `PadmeDAQ`.`run_config_para` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `run_number` INT NOT NULL,
  `config_para_name_id` INT NOT NULL,
  `value` VARCHAR(1024) NOT NULL,
  PRIMARY KEY (`id`),
  INDEX `fk_run_config_para_config_para_name1_idx` (`config_para_name_id` ASC),
  INDEX `fk_run_config_para_run1_idx` (`run_number` ASC),
  CONSTRAINT `fk_run_config_para_config_para_name1`
    FOREIGN KEY (`config_para_name_id`)
    REFERENCES `PadmeDAQ`.`config_para_name` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_run_config_para_run1`
    FOREIGN KEY (`run_number`)
    REFERENCES `PadmeDAQ`.`run` (`number`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `PadmeDAQ`.`l_board_optical_link`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `PadmeDAQ`.`l_board_optical_link` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `board_id` INT NOT NULL,
  `optical_link_id` INT NOT NULL,
  `time_start` DATETIME NULL,
  `time_stop` DATETIME NULL,
  INDEX `fk_l_board_optical_link_board1_idx` (`board_id` ASC),
  INDEX `fk_l_board_optical_link_optical_link1_idx` (`optical_link_id` ASC),
  PRIMARY KEY (`id`),
  CONSTRAINT `fk_l_board_optical_link_board1`
    FOREIGN KEY (`board_id`)
    REFERENCES `PadmeDAQ`.`board` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_l_board_optical_link_optical_link1`
    FOREIGN KEY (`optical_link_id`)
    REFERENCES `PadmeDAQ`.`optical_link` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `PadmeDAQ`.`zsup_process`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `PadmeDAQ`.`zsup_process` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `run_number` INT NOT NULL,
  `daq_process_id` INT NOT NULL,
  `status` INT NOT NULL,
  `time_start` DATETIME NULL,
  `time_stop` DATETIME NULL,
  `n_zsup_files` INT UNSIGNED NULL,
  `total_events` INT UNSIGNED NULL,
  `total_size` BIGINT UNSIGNED NULL,
  PRIMARY KEY (`id`),
  INDEX `fk_zsup_process_run1_idx` (`run_number` ASC),
  INDEX `fk_zsup_process_daq_process1_idx` (`daq_process_id` ASC),
  CONSTRAINT `fk_zsup_process_run1`
    FOREIGN KEY (`run_number`)
    REFERENCES `PadmeDAQ`.`run` (`number`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_zsup_process_daq_process1`
    FOREIGN KEY (`daq_process_id`)
    REFERENCES `PadmeDAQ`.`daq_process` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `PadmeDAQ`.`zsup_proc_config_para`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `PadmeDAQ`.`zsup_proc_config_para` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `zsup_process_id` INT NOT NULL,
  `config_para_name_id` INT NOT NULL,
  `value` VARCHAR(1024) NOT NULL,
  PRIMARY KEY (`id`),
  INDEX `fk_zsup_proc_config_para_config_para_name1_idx` (`config_para_name_id` ASC),
  INDEX `fk_zsup_proc_config_para_zsup_process1_idx` (`zsup_process_id` ASC),
  CONSTRAINT `fk_zsup_proc_config_para_config_para_name1`
    FOREIGN KEY (`config_para_name_id`)
    REFERENCES `PadmeDAQ`.`config_para_name` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_zsup_proc_config_para_zsup_process1`
    FOREIGN KEY (`zsup_process_id`)
    REFERENCES `PadmeDAQ`.`zsup_process` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `PadmeDAQ`.`daq_file`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `PadmeDAQ`.`daq_file` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `daq_process_id` INT NOT NULL,
  `name` VARCHAR(255) NOT NULL,
  `version` INT NULL,
  `part` INT UNSIGNED NULL,
  `time_open` DATETIME NULL,
  `time_close` DATETIME NULL,
  `n_events` INT UNSIGNED NULL,
  `size` BIGINT UNSIGNED NULL,
  PRIMARY KEY (`id`),
  UNIQUE INDEX `daq_file_name_UNIQUE` (`name` ASC),
  INDEX `fk_daq_file_daq_process1_idx` (`daq_process_id` ASC),
  CONSTRAINT `fk_daq_file_daq_process1`
    FOREIGN KEY (`daq_process_id`)
    REFERENCES `PadmeDAQ`.`daq_process` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `PadmeDAQ`.`zsup_file`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `PadmeDAQ`.`zsup_file` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `zsup_process_id` INT NOT NULL,
  `name` VARCHAR(255) NOT NULL,
  `version` INT NULL,
  `part` INT UNSIGNED NULL,
  `time_open` DATETIME NULL,
  `time_close` DATETIME NULL,
  `n_events` INT UNSIGNED NULL,
  `size` BIGINT UNSIGNED NULL,
  PRIMARY KEY (`id`),
  UNIQUE INDEX `zsup_file_name_UNIQUE` (`name` ASC),
  INDEX `fk_zsup_file_zsup_process1_idx` (`zsup_process_id` ASC),
  CONSTRAINT `fk_zsup_file_zsup_process1`
    FOREIGN KEY (`zsup_process_id`)
    REFERENCES `PadmeDAQ`.`zsup_process` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `PadmeDAQ`.`lvl1_process`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `PadmeDAQ`.`lvl1_process` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `run_number` INT NOT NULL,
  `status` INT NOT NULL,
  `time_start` DATETIME NULL,
  `time_stop` DATETIME NULL,
  `n_raw_files` INT UNSIGNED NULL,
  `total_events` INT UNSIGNED NULL,
  `total_size` BIGINT UNSIGNED NULL,
  PRIMARY KEY (`id`),
  INDEX `fk_lvl1_process_run1_idx` (`run_number` ASC),
  CONSTRAINT `fk_lvl1_process_run1`
    FOREIGN KEY (`run_number`)
    REFERENCES `PadmeDAQ`.`run` (`number`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `PadmeDAQ`.`l_daq_file_lvl1_proc`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `PadmeDAQ`.`l_daq_file_lvl1_proc` (
  `lvl1_process_id` INT NOT NULL,
  `daq_file_id` INT NOT NULL,
  INDEX `fk_l_daq_file_lvl1_proc_lvl1_process1_idx` (`lvl1_process_id` ASC),
  INDEX `fk_l_daq_file_lvl1_proc_daq_file1_idx` (`daq_file_id` ASC),
  CONSTRAINT `fk_l_daq_file_lvl1_proc_lvl1_process1`
    FOREIGN KEY (`lvl1_process_id`)
    REFERENCES `PadmeDAQ`.`lvl1_process` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_l_daq_file_lvl1_proc_daq_file1`
    FOREIGN KEY (`daq_file_id`)
    REFERENCES `PadmeDAQ`.`daq_file` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `PadmeDAQ`.`l_zsup_file_lvl1_proc`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `PadmeDAQ`.`l_zsup_file_lvl1_proc` (
  `lvl1_process_id` INT NOT NULL,
  `zsup_file_id` INT NOT NULL,
  INDEX `fk_l_zsup_file_lvl1_proc_lvl1_process1_idx` (`lvl1_process_id` ASC),
  INDEX `fk_l_zsup_file_lvl1_proc_zsup_file1_idx` (`zsup_file_id` ASC),
  CONSTRAINT `fk_l_zsup_file_lvl1_proc_lvl1_process1`
    FOREIGN KEY (`lvl1_process_id`)
    REFERENCES `PadmeDAQ`.`lvl1_process` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_l_zsup_file_lvl1_proc_zsup_file1`
    FOREIGN KEY (`zsup_file_id`)
    REFERENCES `PadmeDAQ`.`zsup_file` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `PadmeDAQ`.`l_daq_proc_lvl1_proc`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `PadmeDAQ`.`l_daq_proc_lvl1_proc` (
  `lvl1_process_id` INT NOT NULL,
  `daq_process_id` INT NOT NULL,
  INDEX `fk_l_daq_proc_lvl1_proc_lvl1_process1_idx` (`lvl1_process_id` ASC),
  INDEX `fk_l_daq_proc_lvl1_proc_daq_process1_idx` (`daq_process_id` ASC),
  CONSTRAINT `fk_l_daq_proc_lvl1_proc_lvl1_process1`
    FOREIGN KEY (`lvl1_process_id`)
    REFERENCES `PadmeDAQ`.`lvl1_process` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_l_daq_proc_lvl1_proc_daq_process1`
    FOREIGN KEY (`daq_process_id`)
    REFERENCES `PadmeDAQ`.`daq_process` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `PadmeDAQ`.`l_zsup_proc_lvl1_proc`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `PadmeDAQ`.`l_zsup_proc_lvl1_proc` (
  `lvl1_process_id` INT NOT NULL,
  `zsup_process_id` INT NOT NULL,
  INDEX `fk_l_zsup_proc_lvl1_proc_lvl1_process1_idx` (`lvl1_process_id` ASC),
  INDEX `fk_l_zsup_proc_lvl1_proc_zsup_process1_idx` (`zsup_process_id` ASC),
  CONSTRAINT `fk_l_zsup_proc_lvl1_proc_lvl1_process1`
    FOREIGN KEY (`lvl1_process_id`)
    REFERENCES `PadmeDAQ`.`lvl1_process` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_l_zsup_proc_lvl1_proc_zsup_process1`
    FOREIGN KEY (`zsup_process_id`)
    REFERENCES `PadmeDAQ`.`zsup_process` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `PadmeDAQ`.`lvl1_proc_config_para`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `PadmeDAQ`.`lvl1_proc_config_para` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `lvl1_process_id` INT NOT NULL,
  `config_para_name_id` INT NOT NULL,
  `value` VARCHAR(1024) NOT NULL,
  PRIMARY KEY (`id`),
  INDEX `fk_lvl1_proc_config_para_config_para_name1_idx` (`config_para_name_id` ASC),
  INDEX `fk_lvl1_proc_config_para_lvl1_process1_idx` (`lvl1_process_id` ASC),
  CONSTRAINT `fk_lvl1_proc_config_para_config_para_name1`
    FOREIGN KEY (`config_para_name_id`)
    REFERENCES `PadmeDAQ`.`config_para_name` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_lvl1_proc_config_para_lvl1_process1`
    FOREIGN KEY (`lvl1_process_id`)
    REFERENCES `PadmeDAQ`.`lvl1_process` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `PadmeDAQ`.`raw_file`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `PadmeDAQ`.`raw_file` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `lvl1_process_id` INT NOT NULL,
  `name` VARCHAR(255) NOT NULL,
  `part` INT UNSIGNED NULL,
  `time_open` DATETIME NULL,
  `time_close` DATETIME NULL,
  `n_events` INT UNSIGNED NULL,
  `size` BIGINT UNSIGNED NULL,
  PRIMARY KEY (`id`),
  UNIQUE INDEX `raw_file_name_UNIQUE` (`name` ASC),
  INDEX `fk_raw_file_lvl1_process1_idx` (`lvl1_process_id` ASC),
  CONSTRAINT `fk_raw_file_lvl1_process1`
    FOREIGN KEY (`lvl1_process_id`)
    REFERENCES `PadmeDAQ`.`lvl1_process` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
