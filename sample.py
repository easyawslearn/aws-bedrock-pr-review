import os
import sqlite3
import hashlib
import yaml
from flask import Flask, request

app = Flask(__name__)

# -------------------------
# 1. SQL Injection Example
# -------------------------
def get_user(user_id):
    conn = sqlite3.connect("users.db")
    cursor = conn.cursor()

    # ❌ Vulnerable: direct string concat allows SQL Injection
    query = f"SELECT * FROM users WHERE id = {user_id};"
    cursor.execute(query)

    result = cursor.fetchall()
    conn.close()
    return result


# -------------------------
# 2. Command Injection Example
# -------------------------
def run_ping(host):
    # ❌ Vulnerable: unsanitized input passed to system command
    os.system("ping -c 1 " + host)


# -------------------------
# 3. Weak Hashing Example
# -------------------------
def hash_password(password):
    # ❌ Vulnerable: MD5 is cryptographically weak
    return hashlib.md5(password.encode()).hexdigest()


# -------------------------
# 4. Unsafe YAML Parsing Example
# -------------------------
def load_config(path):
    with open(path, "r") as f:
        # ❌ Vulnerable: yaml.load allows arbitrary code execution
        return yaml.load(f, Loader=yaml.Loader)
        # CodeQL will recommend yaml.safe_load()


# -------------------------
# 5. Web Endpoint for Testing
# -------------------------
@app.route("/test", methods=["GET"])
def test():
    user_id = request.args.get("id", "1")
    host = request.args.get("host", "127.0.0.1")
    pwd = request.args.get("pwd", "admin")

    # Trigger vulnerabilities
    user = get_user(user_id)
    run_ping(host)
    hashed = hash_password(pwd)

    return {
        "user_output": str(user),
        "hashed_pwd": hashed
    }


if __name__ == "__main__":
    app.run(debug=True)
