CREATE TABLE measurement (
    id INT AUTO_INCREMENT PRIMARY KEY,
    date TIMESTAMP NOT NULL,
    localization varchar(3) NOT NULL,
    dht_humidity Numeric(5,2),
    dht_temperature Numeric(5,2),
    dht_heatindex Numeric(5,2),
    htu_humidity Numeric(5,2),
    htu_temperature Numeric(5,2),
    htu_heatindex Numeric(5,2),
    bmp_temperature Numeric(5,2),
    bmp_preasure Numeric(6,2)
);

{"date": "1970-01-01 00:00:02", "localization": "out", "dht_humidity": 500, "dht_temperature": 203, "dht_heatindex": 204.23, "htu_humidity": 34, "htu_temperature": 24, "htu_heatindex": null, "bmp_temperature": 124.23, "bmp_preasure": 2024.23}