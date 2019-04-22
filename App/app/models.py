from app import db, login
from sqlalchemy.dialects.postgresql import JSON
from flask_login import UserMixin
from werkzeug.security import generate_password_hash, check_password_hash
from datetime import datetime


class RequestsRecord(db.Model):
    __tablename__ = 'Requests'
    id   = db.Column(db.Integer, primary_key=True)
    # name = db.Column(db.String(250), nullable=False, unique=True)
    timestamp = db.Column(db.DateTime, index=True, default=datetime.utcnow)
    user_id = db.Column(db.Integer, db.ForeignKey('Users.id'))
    # result_all = db.Column(JSON)

    def __init__(self, name, time, result_all):
        self.name = name
        self.time = time
        self.result_all = result_all

    def __repr__(self):
        return '<id {}, name {}, time {}>'.format(self.id, self.name, self.time)


class Spot(db.Model):
    __tablename__ = "Parking Spots"
    id    = db.Column(db.Integer, primary_key=True)
    state = db.Column(db.String(250), nullable=False)
    # result_all = db.Column(JSON)

    def __init__(self, state, result_all):
        self.state = state
        self.result_all = result_all

    def __repr__(self):
        return '<id {}, state {}>'.format(self.id, self.state)


class User(UserMixin, db.Model):
    __tablename__ = 'Users'
    id         = db.Column(db.Integer,primary_key=True)
    username   = db.Column(db.String(250), nullable=False, unique=True)
    password_hash   = db.Column(db.String(250), nullable=False)
    requests   = db.relationship('RequestsRecord', backref='driver', lazy='dynamic')
    # result_all = db.Column(JSON)


    def __init__(self, username):
        self.username = username

    def __repr__(self):
        return '<id {}, username {}>'.format(self.id, self.username)

    def set_password(self, password):
        self.password_hash = generate_password_hash(password)

    def check_password(self, password):
        return check_password_hash(self.password_hash, password)

@login.user_loader
def load_user(id):
    return User.query.get(int(id))
