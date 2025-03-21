# <p align = "center"> PAX 
<p align = "center"> Automatiskt bokningssystem för företagslokaler - Chas Challenge 2025  </p> 
      
## **Introduktion och bakgrund**  
### Projektets syfte och mål:
Syftet med PAX är att effektivisera användningen av mötesrum genom ett automatiserat bokningssystem. Sensorer som känner av aktivitet installeras i rummen och kopplas till en app-tjänst. När du är i rummet bokas det automatiskt. Genom appen får användarna en bra överblick över tillgängliga rum. Målet är smidig bokning för användarna, optimering av beläggningen samt möjlighet för datainsamling för statistik och vidare analys. 

### Problemet som lösningen ska addressera:
  Uppbokade mötesrum på större företag och företagshotell, som står tomma.
Medarbetare behöver leta efter tomma rum, då rummen står uppbokade på en viss tid men inte används hela tiden.
Lokalkostnader är bland det dyraste för företag, att kunna växa större i samma lokaler har potential att spara miljonbelopp per år. 
Modifierbart förslag. Automatiskt avbokning av en BRFs lokaler

### Intressenter och målgrupper:  
Större bolag med många anställda som vill kunna boka konferensrum (stor efterfrågan, lågt utbud). 
Det finns potential att spara miljonbelopp per år genom att effektivisera rumsbeläggningen.
Andra typer av anläggningar/verksamheter med rum som används av flera personer, till exempel kontorshotell.

### Teknologier för frontend, backend och IoT.  
    Frontend: React Native, Figma, Tailwind CSS  
    Backend: PostgreSQL, Node.js och Express.js   
    IoT: Arduino, C++,
___

## Teamstruktur och ansvarsområden  
### FMWX24:      
**Medlemmar:** [Tova](https://github.com/tovaalicia), [Hanna](https://github.com/HannaKindholm), [Hannah](https://github.com/HannahVrou)            
#### **Huvudansvar och arbetsuppgifter:**  
Med React Native och Tailwind ta fram en intuitiv och lättanvänd plattform för admin, implementera datavisualisering, bygga upp en mobil applikation för användare.   
Påbörjar layout, form, färg redan innan - fria händer för Frontend i färgen och formen.   
Ta reda på användarbehovet, hur kommer man vilja använda appen - gemensamma beslut samt avcheckning med de andra grupperna inom detta.
Ipad-layout för bokningsskärm utanför konferansrummet.
#### **Teamsamarbete och kunskapsöverföring:**  
Ta del av den data som kommer behövas i form av API:er från backend. Lämna rapport efter boiler room vad vi gjort och vilka utmaningar vi mött. Stand up-möte på Tisdagar där minst en Frontend:are representerar. Skapa en read.me fil för dokumentation. 
___
### SUVX24:      
**Medlemmar:** [Jennifer](https://github.com/simbachu), [Erik](https://github.com/erikdsp), [Oscar](https://github.com/NewNamesAreHard), [Sabina](https://github.com/binasime), [Johan](https://github.com/bubba-94)            
#### **Huvudansvar och arbetsuppgifter:**  
Bygga och utveckla hårdvarasom med hjälp av sensorer kommunicerar med en API för datahantering.  
- Kontrollenhet för rummet
- Dataöverföring/kommunikation med backend via USB/WiFi
- Sensorer för att känna av rummets status:
  - IR-Laser
  - Mikrofon (högupplöst, billig kondensator)
  - Luftkvalitetssensor
#### **Teamsamarbete och kunskapöverföring:**  
Gemensam planering och arbete under både projektdagar och Boiler Rooms.  
___   

### FJSX24:      
**Medlemmar:** [Dennis](https://github.com/TheUnseenBug), [Alice](https://github.com/alicegmn), [Rhiannon](https://github.com/Rhibro), [Phithai]()       
#### **Huvudansvar och arbetsuppgifter:**   
Bygga databas och API för att hantera data från sensorer och skicka vidare den i en användbar form till frontend.  
Databas för att spara vilka konferensrum som är bokade. API-dokumentation.

#### **Teamsamarbete och kunskapöverföring:**  

___

### Teamwork och säker kunskapsöverföring:  
Efter varje team har haft sin gemensamma arbetstid (boiler room), lämna en rapport i ett gemensamt dokument med vad som gjorts tex.  
Varje team (frontend, backend & iot) har en teamleader, dessa tre har det yttersta ansvaret att synka mellan teamen.  
Alla måste kommunicera inom gruppen och vara med på tisdagsmöten enligt gruppkontraktet.
___  

## Arbetsmetodik och verktyg:  
- Vilka verktyg som ska användas för:
  - Kodhantering: Github-repo (i en org.)
  - Kommunikation: Slack
  - Sprint-planering: GitHub projects
- Standups/ceremonier/möten:
  - Arbetsmöte i stor grupp tisdagar kl 9.00.
  - Intern sprintplanering i Boiler Room grupperna där retros och demos också planeras ihop under projektdagar (eventuellt gruppledare kan gå igenom resultat tillsammans).

___  

## Tidsplan och milstolpar:  
- V. 10–11: Research, val av projekt (inkl.hårdvara)
- V. 12: skapande av projektplan.Fredag 21/3: 15.00 Projektplanen skickas in för godkännande.
- V. 13: Paus!
- V. 14: Arbetsmöte Kursen startar “på riktigt” - vi börjar arbeta i
- V. 15: Fullstack: Få upp endpoints till ett API med mockad data.
- V. 16: Implementering av kärnfunktioner. 
- V. 17: MVP.
- V. 18: Fullstack: Integrerad databas och ersatt mockad data.
- V. 19:
- V. 20:
- V. 21:
- V. 22: Testning, förbättring och optimering. Fullstack: Implementerat säkerhet med JWT.
- V. 23: Projektavslut (demo, uppvisning, retro).
Hur hanterar temaet förändringar i tidsplanen om någor tar längre tid än förväntat?
Kommunikation och agilt arbete. Vi testar allting löpande
______

## Riskanalys och plan för problemhantering: 
- **Vilka risker kan uppstå? (ex. tekniska utmaningar, brist på kommunikation, tidsbrist).**
  Bristande kommunikation om vi inte håller varandra uppdaterade, brist på förståelse vid olika termer.   
  Frontend kan behöva vänta på att backend ska bli klar med API:er.   
  Versionshantering där konflikter kan uppstå. Orealistiska deadlines samt olika arbetstempo kan också bli hinder.
- **Hur ska ni hantera problem som blockerar utvecklingen?**  
  Regelbundna standups och tydliga arbetsfördelningar. 
  Meddela i första hand ditt egna “team” om man stöter på problem, blir det ett större problem så meddela även de andra teamen.  
- **Vilka steg tar ni om en teammedlem inte levererar enligt plan?**  
  I första hand prata med den berörda, finns det någon bakomliggande anledning? Går det att lösa? 
____

## Leveranser och dokumenation:  
Vad varje team (frontend, backend, IoT) måste leverera vid projektavslut
  - Fullstack:
    - API för datainsamling och hantering av händelser
    - Generera notifieringar till appen baserade på sensordata
    - Databas för lagring och analys
    - Autentisering och rollhantering
      
  - Frontend:
    - Ta emot API från backend
    - WCAG Layout
    - Funktionella komponenter som pratar med backend och sensorerna

  - IoT:
    - 
- Vilken dokumentation som ska finnas och vem som ansvarar för den?
  - Vardera team ansvarar för sin egna dokumentation.
- Plan för att hålla README och API-dokumentation uppdaterad

## Slutlig checklista 
  - Dokumenteras som PROJEKTPLAN.md i Git-repot
  - Ska innehålla alla ovanstående punkter innan inlämning vecka 12
  - Projektplanen skickas till respektive utbildare senast den 21/3 kl 15.00
  - Godkännas av utbildare innan utvecklingsarbetet startar






