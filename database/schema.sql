CREATE DATABASE IF NOT EXISTS handover_db;

USE handover_db;

CREATE TABLE IF NOT EXISTS handover_records (
    id INT AUTO_INCREMENT PRIMARY KEY,
    timestamp DATETIME NOT NULL,
    ue_id VARCHAR(50) NOT NULL,

    source_cell VARCHAR(50) NOT NULL,
    target_cell VARCHAR(50) NOT NULL,

    source_rsrp DOUBLE,
    target_rsrp DOUBLE,

    source_rsrq DOUBLE,
    target_rsrq DOUBLE,

    source_sinr DOUBLE,
    target_sinr DOUBLE,

    result VARCHAR(20) NOT NULL
);
