import os
from flask import Flask, abort, request
from mysql import Mysql
from logger import log

app = Flask(__name__)
mySql = Mysql()

ESP_API_TOKEN = os.getenv('ESP_API_TOKEN')

@app.route('/esp', methods=['POST'])
def esp():
    log.info('Run /esp')

    buff = request.data.decode('utf-8')
    lines = buff.split('\n')
    log.debug(buff)

    if 'token' not in request.headers:
        log.error('No header')
        abort(417)
    elif request.headers['token'] != ESP_API_TOKEN:
        log.error('Invalid token: ' + request.headers['token'])
        abort(401)
    else:
        log.info('Insert data to DB')
        for row in lines:
            log.debug(row)
            if not mySql.tryToInsert(row):
                log.error('Database error')
                abort(422)
    return "xD"

@app.route('/result', methods=['GET'])
def result():
    abort(404)

@app.route('/health', methods=['GET'])
def health():
    log.info('Checking /health')

    result = mySql.tryToSelect()
    result = result.one()

    return str(result)

@app.route('/')
def main():
    log.warn('Someone is comming')
    return 'Hell!'
