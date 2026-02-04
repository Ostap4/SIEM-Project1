from flask import Flask, render_template, request, flash
import socket

app = Flask(__name__)
app.secret_key = 'super_tajny_klucz'


UDP_IP = "127.0.0.1"
UDP_PORT = 5555

def send_siem_log(ip, event, result, user, password_hash):
   
    msg = f"{ip}|{event}|{result}|{user}|{password_hash}"
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.sendto(msg.encode('utf-8'), (UDP_IP, UDP_PORT))
        print(f"[SIEM LOG] Wysłano: {msg}")
    except Exception as e:
        print(f"[BLAD] Nie udało się wysłać logu do SIEM: {e}")


def get_client_ip():
 
    if request.headers.getlist("X-Forwarded-For"):
         
        return request.headers.getlist("X-Forwarded-For")[0]
    
    return request.remote_addr

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        
        user_ip = get_client_ip() 
        
        
        if username == 'admin' and password == '132':
            send_siem_log(user_ip, "LOGIN", "SUCCESS", username, "hash_correct")
            return f"<h1>Witaj {username}! Zalogowano pomyślnie z IP: {user_ip}</h1>"
        else:
            send_siem_log(user_ip, "LOGIN", "FAILURE", username, "hash_bad")
            flash(f'Błąd logowania! Twoje IP: {user_ip}', 'danger')
            
    return render_template('login.html')

if __name__ == '__main__':
    app.run(host="0.0.0.0", port=UDP_PORT, debug=True)
