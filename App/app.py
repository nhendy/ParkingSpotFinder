from flask import (Flask)
import datetime
from sqlalchemy import Column, Integer, String, DateTime
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import create_engine
from blueprints import auth, blog, PI
Base = declarative_base()

class Users(Base):
    __tablename__ = 'users'
    userID = Column(Integer,primary_key=True,autoincrement=True)
    username = Column(String(250), nullable=False, unique=True)
    password = Column(String(250), nullable=False)
    reservation_state = Column(String(250),nullable=False)
    timestamp = Column(DateTime, default=datetime.datetime.utcnow)
    code = Column(Integer)

app = Flask(__name__, instance_relative_config=True)
app.secret_key = "super_secret_key"

def initialise_databases():
    engine_users = create_engine('sqlite:///userCredentialsDB.db')
    Base.metadata.create_all(engine_users)
    return None

if __name__ == "__main__":
    reserved_spots = 0
    app.register_blueprint(auth.bp)
    app.register_blueprint(blog.bp)
    app.register_blueprint(PI.bp)
    initialise_databases()
    app.run()
