import sqlite3

import click
from flask import current_app, g
from flask.cli import with_appcontext
import app
from sqlalchemy.ext.automap import automap_base
from sqlalchemy import Column, ForeignKey, Integer, String
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import relationship, sessionmaker
from sqlalchemy import create_engine, select

def load_db(database):
    db = "sqlite:///" + database + ".db"
    engine = create_engine(db)
    app.Base.metadata.bind = engine
    DBSession = sessionmaker(bind=engine)
    session = DBSession()
    return session