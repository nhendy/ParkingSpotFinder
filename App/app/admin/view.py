from flask_admin.contrib import sqla
import flask_login as login


class AdminModelView(sqla.ModelView):
    def is_accessible(self):
        return login.current_user.is_authenticated

    def inaccessible_callback(self, name, **kwargs):
        return redirect(url_for('auth.login', next=request.url))