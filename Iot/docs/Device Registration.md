# Registrera en enhet
## UUID
Varje enhet har ett unikt ID lagrat i enheten. På produktionsenhet skulle detta brännas in i en EEPROM el. dyl, och tryckas på en etikett på baksidan.

## Koppling mellan UUID och rum
På backendserver kopplar man en enhets UUID till ett rum. När enheten startar kollar den om den har ett lagrat rums-id. Om inte, ber den servern om ett rumsid via api /device-config/{uuid}. Om det finns ett registrerat rum, skickas det tillbaka och lagras på enheten. Om det inte finns ett registrerat rum, skall detta visas på admin-interface där man ombeds tilldela ett rum.

## Montering i rummet
Vid instalation monteras enheten i det rummet som är angivet i backend.
