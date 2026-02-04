import socket
import time
import random
import sys
sys.stdout.reconfigure(encoding="utf-8")
UDP_IP = "127.0.0.1"
UDP_PORT = 5555
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)


BRUTE_SUCCESS_IP = "192.168.99.99"  
ENUM_IP = "172.16.55.55"          

def send_log(ip, event, result, user, password):
    
    msg = f"{ip}|{event}|{result}|{user}|{password}"
    sock.sendto(msg.encode('utf-8'), (UDP_IP, UDP_PORT))
    print(f"[LOG] -> {msg}")

def simulate_brute_force_success():
    target_user = "admin"
    print(f"\n--- SCENARIUSZ: Atak na konto '{target_user}' z sukcesem ---")
    print(f"Haker: {BRUTE_SUCCESS_IP}")
    
    passwords = ["123", "admin", "pass", "qwerty", "toor"]
    for p in passwords:
        send_log(BRUTE_SUCCESS_IP, "LOGIN", "FAILURE", target_user, p)
        time.sleep(0.3) 
        
   
    print(">>> HAKER TRAFIŁ HASŁO! <<<")
    time.sleep(0.5)
    send_log(BRUTE_SUCCESS_IP, "LOGIN", "SUCCESS", target_user, "P@$$w0rd_Correct")
    print("--- Koniec scenariusza ---")

def simulate_user_enumeration():
    print(f"\n--- SCENARIUSZ: Skanowanie użytkowników (Enumeration) ---")
    print(f"Haker: {ENUM_IP}")
    print("Próba logowania na wiele różnych kont z jednego miejsca...")
 
    target_users = ["root", "admin", "administrator", "user", "guest", "test", "sql_admin", "hr_manager"]
    
    for user in target_users:
   
        send_log(ENUM_IP, "LOGIN", "FAILURE", user, "password123")
        time.sleep(0.2)
        
    print("--- Koniec scenariusza ---")

while True:
    print("\n" + "="*40)
    print("   SIEM ADVANCED SIMULATOR v3.0")
    print("="*40)
    print("1. Pojedynczy log (Normalny ruch)")
    print("2. Atak BRUTE-FORCE (Tylko błędy)")
    print("3. Atak DDoS (Flood)")
    print("-" * 30)
    print("4. TEST KORELACJI: Brute-Force + SUKCES")
    print("5. TEST KORELACJI: User Enumeration (Różni userzy)")
    print("-" * 30)
    print("0. Wyjście")
    
    choice = input("\nWybierz opcję: ")
    
    if choice == '1':
        send_log("192.168.1.10", "LOGIN", "SUCCESS", "user", "pass")
    elif choice == '2':

        for i in range(10):
            send_log("66.66.66.66", "LOGIN", "FAILURE", "admin", "badpass")
            time.sleep(0.1)
    elif choice == '3':

        for i in range(50):
            send_log("10.10.10.10", "PING", "info", "bot", "flood")
    elif choice == '4':
        simulate_brute_force_success()
    elif choice == '5':
        simulate_user_enumeration()
    elif choice == '0':
        break
    else:
        print("Nieznana opcja.")