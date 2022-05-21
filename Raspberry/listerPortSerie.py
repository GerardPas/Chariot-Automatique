#!/usr/bin/python3
import serial.tools.list_ports as lp

def liste_ports_serie_disponibles():
    ''' liste tous les ports série disponibles '''
    ports = lp.comports()
    return [(port, desc, hwid) for port, desc, hwid in sorted(ports)]

def trouve_port():
    '''
    retourne le nom complet du port
    correspondant aux identifiants vendeur et machine USB (VID:PID)
    '''
    for port, desc, hwid in lp.grep('10C4:EA60'):
        return port
    else:
        return 'périphérique introuvable'

''' Afficher tous les ports série '''
for port_infos in liste_ports_serie_disponibles():
    port, desc, hwid = port_infos
    print(f"Port: {port}\tDescription: {desc}\t  hwid: {hwid}")

''' Afficher le nom du port série qui correspond au périphérique USB
    dont les identifiants sont VID:PID = 10C4:EA60
'''

port = trouve_port()
print(f"\nLe nom du port du périphérique VID:PID = 10C4:EA60 est : {port}")
    