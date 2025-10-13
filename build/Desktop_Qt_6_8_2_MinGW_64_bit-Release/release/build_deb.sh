#!/bin/bash

# Configurazione
APP_NAME="timer"
VERSION="2.0"
ARCHITECTURE="amd64"

# Pulisci build precedenti
rm -rf deb-build
mkdir -p deb-build/${APP_NAME}-${VERSION}/DEBIAN
mkdir -p deb-build/${APP_NAME}-${VERSION}/opt/timer
mkdir -p deb-build/${APP_NAME}-${VERSION}/opt/timer/ASCIIVideoPlayer
mkdir -p deb-build/${APP_NAME}-${VERSION}/usr/bin
mkdir -p deb-build/${APP_NAME}-${VERSION}/usr/share/applications
mkdir -p deb-build/${APP_NAME}-${VERSION}/usr/share/icons/hicolor/256x256/apps

# Copia i file dell'applicazione
cp Timer deb-build/${APP_NAME}-${VERSION}/opt/timer/
cp config deb-build/${APP_NAME}-${VERSION}/opt/timer/
cp ASCIIVideoPlayer/ASCIIVideoPlayer deb-build/${APP_NAME}-${VERSION}/opt/timer/ASCIIVideoPlayer/

mkdir -p deb-build/${APP_NAME}-${VERSION}/opt/timer/ASCIIVideoPlayer/txt
cp -r ASCIIVideoPlayer/txt/ deb-build/${APP_NAME}-${VERSION}/opt/timer/ASCIIVideoPlayer/txt/
cp ASCIIVideoPlayer/My.mp3 deb-build/${APP_NAME}-${VERSION}/opt/timer/ASCIIVideoPlayer/

# COPIA SOLO L'ICONA 256x256 (LA PIÙ IMPORTANTE)
if [ -f "../../../../pendulum.png" ]; then
    cp ../../../../pendulum.png deb-build/${APP_NAME}-${VERSION}/usr/share/icons/hicolor/256x256/apps/timer.png
    echo "Icona copiata: 256x256"
else
    echo "Warning: icon.png non trovata, creo placeholder..."
    # Crea un'icona placeholder semplice
    convert -size 256x256 xc:blue -pointsize 50 -fill white -gravity center -annotate +0+0 "Timer" deb-build/${APP_NAME}-${VERSION}/usr/share/icons/hicolor/256x256/apps/timer.png
fi

# Crea control file
cat > deb-build/${APP_NAME}-${VERSION}/DEBIAN/control << EOF
Package: ${APP_NAME}
Version: ${VERSION}
Section: utils
Priority: optional
Architecture: ${ARCHITECTURE}
Depends: libqt6core6, libqt6gui6, libqt6widgets6, libsdl2-2.0-0, libsdl2-mixer-2.0-0
Maintainer: Tizzycek <tizianoceccon@outlook.it>
Description: Applicazione Timer
 Un timer che fa trascorrere l'attesa senza noia.
EOF

# Crea script di lancio
cat > deb-build/${APP_NAME}-${VERSION}/usr/bin/timer << 'EOF'
#!/bin/bash
cd /opt/timer
./Timer "$@"
EOF

# Crea desktop file
cat > deb-build/${APP_NAME}-${VERSION}/usr/share/applications/timer.desktop << EOF
[Desktop Entry]
Name=Timer
Comment=Timer Application with ASCII Video Player
Exec=timer
Icon=timer
Type=Application
Categories=Utility;
Terminal=false
StartupNotify=true
EOF

# Crea postinst script per aggiornare cache icone
cat > deb-build/${APP_NAME}-${VERSION}/DEBIAN/postinst << 'EOF'
#!/bin/bash
set -e

# Aggiorna cache icone
if command -v update-icon-caches >/dev/null; then
    update-icon-caches /usr/share/icons/hicolor
elif command -v gtk-update-icon-cache >/dev/null; then
    gtk-update-icon-cache -f -t /usr/share/icons/hicolor
fi

# Aggiorna database desktop
update-desktop-database /usr/share/applications || true

# Imposta permessi
chmod 755 /opt/timer/Timer
chmod 755 /opt/timer/ASCIIVideoPlayer/ASCIIVideoPlayer

# 1. Configura per utenti FUTURI (tramite /etc/skel)
mkdir -p /etc/skel/.local/share/Timer
if [ -f "/opt/timer/config" ] && [ ! -f "/etc/skel/.local/share/Timer/config" ]; then
    cp "/opt/timer/config" "/etc/skel/.local/share/Timer/" 2>/dev/null || true
fi
touch /etc/skel/.local/share/Timer/stop.flag 2>/dev/null || true

# 2. Configura per utenti ESISTENTI
for USER_HOME in /home/*; do
    if [ -d "$USER_HOME" ] && [ "$USER_HOME" != "/home/lost+found" ]; then
        USER=$(basename "$USER_HOME")
        mkdir -p "$USER_HOME/.local/share/Timer"
        
        if [ -f "/opt/timer/config" ] && [ ! -f "$USER_HOME/.local/share/Timer/config" ]; then
	    echo "cp /opt/timer/config $USER_HOME/.local/share/Timer/ 2>/dev/null"
            cp "/opt/timer/config" "$USER_HOME/.local/share/Timer/" 2>/dev/null || true
        fi
        
        if [ ! -f "$USER_HOME/.local/share/Timer/stop.flag" ]; then
            touch "$USER_HOME/.local/share/Timer/stop.flag" 2>/dev/null || true
        fi
        
        chown -R "$USER:$USER" "$USER_HOME/.local/share/Timer" 2>/dev/null || true
    fi
done

exit 0
EOF

# Crea prerm script
cat > deb-build/${APP_NAME}-${VERSION}/DEBIAN/prerm << 'EOF'
#!/bin/bash
set -e

# Pulizia prima della disinstallazione

# 1. Rimuovi desktop file
rm -f /usr/share/applications/timer.desktop

# 2. Rimuovi configurazioni per utenti ESISTENTI
for USER_HOME in /home/*; do
    if [ -d "$USER_HOME" ] && [ "$USER_HOME" != "/home/lost+found" ]; then
        USER=$(basename "$USER_HOME")
        
        # Rimuovi directory Timer dell'utente
        rm -rf "$USER_HOME/.local/share/Timer" 2>/dev/null || true
        rm -rf "$USER_HOME/.config/Timer" 2>/dev/null || true
        
        echo "Rimosso configurazione per utente: $USER"
    fi
done

# 3. Rimuovi configurazioni da /etc/skel (utenti futuri)
rm -rf /etc/skel/.local/share/Timer 2>/dev/null || true
rm -rf /etc/skel/.config/Timer 2>/dev/null || true

# 4. Rimuovi icona (opzionale - se vuoi pulire tutto)
# rm -f /usr/share/icons/hicolor/*/apps/timer.png 2>/dev/null || true

echo "Pulizia configurazione Timer completata"
exit 0
EOF

# Imposta i permessi
chmod 755 deb-build/${APP_NAME}-${VERSION}/usr/bin/timer
chmod 755 deb-build/${APP_NAME}-${VERSION}/opt/timer/Timer
chmod 755 deb-build/${APP_NAME}-${VERSION}/opt/timer/ASCIIVideoPlayer/ASCIIVideoPlayer
chmod 755 deb-build/${APP_NAME}-${VERSION}/DEBIAN/postinst
chmod 755 deb-build/${APP_NAME}-${VERSION}/DEBIAN/prerm

# Calcola la dimensione del pacchetto
SIZE=$(du -s deb-build/${APP_NAME}-${VERSION} | cut -f1)
sed -i "s/^Installed-Size:.*/Installed-Size: $SIZE/" deb-build/${APP_NAME}-${VERSION}/DEBIAN/control

# Build del pacchetto
dpkg-deb --build deb-build/${APP_NAME}-${VERSION}

# Rinomina il pacchetto
mv deb-build/${APP_NAME}-${VERSION}.deb ${APP_NAME}_${VERSION}_${ARCHITECTURE}.deb

echo "Pacchetto creato: ${APP_NAME}_${VERSION}_${ARCHITECTURE}.deb"
