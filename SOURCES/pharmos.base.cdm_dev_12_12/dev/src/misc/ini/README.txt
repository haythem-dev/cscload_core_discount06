the voodoo server ports for application logins for UADM are defined in
/etc/services

e.g.
global_login    	58001/tcp       # globale User-Anmeldung
global_usradm		58002/tcp       # Admin fuer User-Anmeldung

the voodoo pipe names can be found in the .sh files
/software/wss/de/uadm/proc/login.sh		loguiserv	# globale User-Anmeldung
/software/wss/de/uadm/proc/uadm.sh		usradmuiserv	# Admin fuer User-Anmeldung
