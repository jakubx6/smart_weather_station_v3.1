import os
import sqlalchemy
from sqlalchemy import create_engine, text, MetaData, Table, Column, Integer, Numeric, String, TIMESTAMP
from flask import g
from logger import log
from dotenv import load_dotenv

load_dotenv('.env')

class Mysql:
    MYSQL_DB_HOST = os.getenv('MYSQL_DB_HOST')
    MYSQL_DB_PORT = os.getenv('MYSQL_DB_PORT')
    MYSQL_DB_USER = os.getenv('MYSQL_DB_USER')
    MYSQL_DB_PASSWORD = os.getenv('MYSQL_DB_PASSWORD')
    MYSQL_DB_NAME = os.getenv('MYSQL_DB_NAME')
    SELECT = 1
    INSERT = 2

    meta = MetaData()
    measurement = Table(
        'measurement', meta,
        Column('id', Integer, primary_key = True), 
        Column('date', TIMESTAMP),
        Column('localization', String),
        Column('dht_humidity', Numeric),
        Column('dht_temperature', Numeric),
        Column('dht_heatindex', Numeric),
        Column('htu_humidity', Numeric),
        Column('htu_temperature', Numeric),
        Column('htu_heatindex', Numeric),
        Column('bmp_temperature', Numeric),
        Column('bmp_preasure', Numeric),
    )

    def tryToSelect(self, query = 'SELECT NOW()'):
        return self.tryTemplate(self.SELECT, query)
        
    def tryToInsert(self, data):
        return self.tryTemplate(self.INSERT, data)

    def tryTemplate(self, type, data):
        db = self.get_db()
        try:
            if type == self.SELECT:
                result = db.execute(text(data))
            elif type == self.INSERT:
                result = False
                db.execute(self.measurement.insert(), data)
                db.commit()
                result = True
        except sqlalchemy.exc.OperationalError as e:
            msg = f'sqlalchemy.exc.OperationalError: {e}'
            log.error(msg)
        except Exception as e:
            msg = f'Error performing operation: {e}'
            log.error(msg)
        self.close_db()
        return result

    def get_db(self):
        if "db" not in g:
            log.info("Connecting to database")
            engine = create_engine(
                f"mysql+pymysql://{self.MYSQL_DB_USER}:{self.MYSQL_DB_PASSWORD}@{self.MYSQL_DB_HOST}:{self.MYSQL_DB_PORT}/{self.MYSQL_DB_NAME}?charset=utf8mb4",
                pool_pre_ping=True,
            )
            g.db = engine.connect()

            return g.db

    def close_db(self, e = None):
        log.info("close_db requested")
        db = g.pop("db", e)
        if db is not None:
            log.info("Closing db connection")
            db.close()
        else:
            log.info("db connection already closed. No action taken.")
