import os
import requests
from flask import Flask, session
from flask import current_app, g
import sqlite3

from sqlalchemy import Column, ForeignKey, Integer, String
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import relationship, sessionmaker
from sqlalchemy import create_engine

Base = declarative_base()
class RequestsRecord(Base):
    __tablename__ = 'requests_record'
    id = Column(Integer, primary_key=True,autoincrement=True)
    name = Column(String(250), nullable=False)
    #time = Column(datetime, nullable=False)

class Spots(Base):
    __tablename__ = "spots"
    id = Column(Integer, primary_key=True,autoincrement=True)
    state = Column(String(250), nullable=False)

class Users(Base):
    __tablename__ = 'users'
    userID = Column(Integer,primary_key=True,autoincrement=True)
    username = Column(String(250), nullable=False)
    password = Column(String(250), nullable=False)

app = Flask(__name__, instance_relative_config=True)
app.secret_key = "super_secret_key"

def initialise_databases():
    engine_userRequests = create_engine('sqlite:///userRequestsDB.db')
    engine_userCredentials = create_engine('sqlite:///userCredentialsDB.db')
    engine_parkingSpots = create_engine('sqlite:///parkingSpotsDB.db')
    Base.metadata.create_all(engine_userRequests)
    Base.metadata.create_all(engine_userCredentials)
    Base.metadata.create_all(engine_parkingSpots)
    return None

if __name__ == "__main__":
    import auth, blog
    app.register_blueprint(auth.bp)
    app.register_blueprint(blog.bp)
    initialise_databases()
    app.run()
