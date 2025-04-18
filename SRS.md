# Inledning

# Innehållsförteckning

1. [Introduktion](#1-introduktion)

   1.1 [Syfte](#11-syfte)

   1.2 [Omfattning](#12-omfattning)

2. [Övergripande Beskrivning](#2-övergripande-beskrivning)
3. [Specifika Krav](#3-specifika-krav)
4. [Systemarkitektur och Designkrav](#4-systemarkitektur-och-designkrav)
5. [Projektorganisation och Utvecklingsmetodik](#5-projektorganisation-och-utvecklingsmetodik)
6. [Testning och Kvalitetssäkring](#6-testning-och-kvalitetssäkring)
7. [Riskanalys och Problemhantering](#7-riskanalys-och-problemhantering)
8. [Tidsplan och Milstolpar](#8-tidsplan-och-milstolpar)
9. [Leveranser och Dokumentationskrav](#9-leveranser-och-dokumentationskrav)
10. [Sammanfattning](#10-sammanfattning)

# 1. Introduktion

## 1.1 Syfte

Syftet med detta dokument är att definiera och specificera krav samt övergripande funktionalitet för systemet PAX. Systemet ska effektivisera bokningen av företagslokaler genom ett automatiserat processflöde där sensorer registrerar närvaro och systemet via en app bokar rum automatiskt. Dokumentet riktar sig till respektive utvecklingsteam och projektledare samt andra intressenter.

## 1.2 Omfattning

PAX är ett automatiserat bokningssystem där varje mötesrum utrustas med sensorer som mäter aktivitet och miljödata (t.ex. PIR-sensor, mikrofon, luftkvalitetssensor). Den insamlade datan hanteras av en IoT-komponent som kommunicerar med en backend via ett API, där data lagras i en PostgreSQL-databas. Frontend-komponenten, byggd med React Native, ger användaren en översikt över tillgängliga och bokade rum samt notifierar om statusförändringar. Systemet ämnar öka utnyttjandegraden av rummen och därigenom minska lokalkostnader för företagen.

## 1.3 Definitioner och Akronymer

**PAX**: Projektnamnet för vårat samlade system, UI/UX, infrastruktur samt inbyggda systemet.

**IoT**: Internet of Things, enheter som kommunicerar och övervakar fysiska parametrar.

**API**: Application Programming Interface, gränssnitt för kommunikation mellan systemets olika enheter.

**MVP**: Minimum Viable Product, den minsta versionen med kärnfunktionalitet som behövs för att vara användbar.

**WCAG**: Web Content Accessibility Guidelines, standard för tillgänglig design.

**JWT**: JSON Web Token, standard för säkrad autentisering.

**Frontend/Backend**: Klient- respektive serversidan av systemet.

# 2. Övergripande Beskrivning

## 2.1 Produktperspektiv

PAX är en fristående lösning som ska integreras i större företags- och företagshotellsmiljöer. Systemet fungerar både som ett operativt bokningsverktyg och som en dataansamlingstjänst för framtida analyser. Genom att automatiskt registrera om rummen används, optimeras utnyttjandegraden och ekonomiska besparingar kan uppnås.

## 2.2 Produktfunktioner

**Automatisk bokning**: Närvaro i rummet registreras via installerade sensorer, vilket exempelvis kan resulterar i en omedelbar (av)bokning genom systemet.

**Användarvänlig app**: Användargränssnittet ger en översikt över mötesrum, bokningsstatus och historik.

**Notifieringssystem**: Systemet genererar notifieringar baserat på sensordata (t.ex. om ett rum plötsligt blir tillgängligt).

**Datainsamling och analys**: Data lagras och används för att skapa statistik över rumsutnyttjande, vilket möjliggör framtida optimeringar.

**Flexibilitet**: Möjlighet att anpassa lösningen även för andra typer av anläggningar, exempelvis kontorshotell eller bostadsrättsföreningar.

## 2.3 Målgrupper och Intressenter

**Primär målgrupp**: Större företag med många anställda, företagshotell och andra organisationer med stort behov av mötesrum.

**Sekundär målgrupp**: Leverantörer av anläggningar med flera delade rum, t.ex. kontorshotell eller bostadsrättsföreningar.

### Projektteam: Bestående av tre subteam:

**Frontend (FMWX24)**: Ansvarar för app-utveckling med React Native, gränssnittsdesign (Tailwind CSS, Figma) samt datavisualisering.

**IoT (SUVX24)**: Ansvarar för hårdvara, sensorintegration (Arduino, C++) samt datainsamling.

**Backend (FJSX24)**: Ansvarar för API:er, databasutveckling (PostgreSQL) samt säkerhet (JWT).

## 2.4 Antaganden och Beroenden

**Tekniska antaganden**:

Systemet kommer att kunna anslutas via trådbundna och trådlösa nätverk (Ethernet/WiFi) mellan IoT-enheterna och backend.

Användare har tillgång till en mobil enhet med appen installerad.

**Beroenden**:

Kommunikation och datadelning mellan IoT-enheter, backend och frontend.

Regelbundna uppdateringar och synkronisering mellan de olika teamens leveranser.

# 3. Specifika Krav

## 3.1 Funktionella Krav

### 3.1.1 Bokningslogik och Automatisering

- FK1: Systemet ska kunna automatiskt (av)boka ett mötesrum när närvarosensorer registrerar aktivitet.

- FK2: Appen ska realtidsvis visa en översikt över vilka rum som är bokade samt vilka som är lediga.

- FK3: Systemet ska uppdatera bokningsstatus baserat på kontinuerlig sensorövervakning.

- FK4: Vid avvikande händelser (t.ex. sensorfel) ska systemet generera en notifiering till administratören.

### 3.1.2 Användargränssnitt

- FK5: Mobilapplikationen ska tillhandahålla ett intuitivt och tillgängligt gränssnitt enligt WCAG-standarder.

- ~~FK6: En separat layout (t.ex. iPad-layout) ska finnas för bokningsskärmar utanför konferensrummen.~~

- FK7: Appen ska kunna kommunicera med backend-API:et för att hämta aktuell data och skicka bokningsinformation.

### 3.1.3 API och Datakommunikation

- FK8: Ett robust API ska utvecklas för att hantera dataöverföring mellan IoT-enheterna, databasen och frontend-applikationen.

* FK9: API:et ska erbjuda endpoints för autentisering, datainsamling, statusuppdateringar och notifieringar.

* FK10: Systemet ska implementera JWT för att säkerställa säker åtkomst och hantering av känsliga data.

### 3.1.4 IoT-integration

- FK11: Hårdvaran ska inkludera sensorer såsom PIR-sensor, mikrofon och luftkvalitetssensor som kan kommunicera med kontrollenheten.

- FK12: Kontrollpanelen för varje mötesrum ska övervaka och hantera sensordata i realtid.

- FK13: Firmware för mikrokontroller (programmerad i C++) ska möjliggöra skalbar hantering av sensorinformationen och kommunikation med backend.

### 3.1.5 Databashantering

- FK14: En PostgreSQL-databas ska implementeras för att lagra bokningsdata, sensorhändelser och användarinformation.

- FK15: Backend-systemet ska möjliggöra datainsamling för att senare kunna genomföra analys och generera statistik.

## 3.2 Icke-Funktionella Krav

### 3.2.1 Prestanda och Skalbarhet

- IFK1: Systemet ska klara av hög belastning och många samtidiga användare, särskilt under mötestider.

- IFK2: API:et ska utformas för låg responstid vid kommunikation mellan IoT-enheter, backend och mobilapp.

### 3.2.2 Säkerhet

- IFK3: Systemet ska implementera säker autentisering med JWT.

- ~~IFK4: Dataöverföring ska ske över säkra kommunikationskanaler (t.ex. HTTPS) för att förhindra obehörig åtkomst.~~

- IFK5: Roller och behörigheter ska definieras noggrant för att säkerställa att endast behöriga användare får tillgång till kritiska funktioner.

### 3.2.3 Tillförlitlighet och Underhållbarhet

- IFK6: Systemet ska vara robust nog att hantera sensorfel samt kommunikationsavbrott med möjlighet till automatisk återkoppling.

- IFK7: Tydlig och uppdaterad dokumentation ska finnas för varje systemkomponent, vilket möjliggör underhåll och vidareutveckling.

- IFK8: Versionshantering ska ske genom GitHub och arbeta med agila metoder med regelbundna standups och retrospektiv.

### 3.2.4 Användbarhet

- IFK9: Användargränssnittet ska utformas med fokus på enkelhet och intuitivitet, baserat på användarbehov och tidiga användartester.

- IFK10: Systemet ska erbjuda tydliga notifieringar samt felmeddelanden vid driftstörningar.

# 4. Systemarkitektur och Designkrav

## 4.1 Teknisk Arkitektur

**Frontend**: Utvecklas med React Native och Tailwind CSS med designstöd från Figma för att säkerställa ett enhetligt, responsivt gränssnitt.

**Backend**: Byggs med Node.js och Express.js för att exponera ett RESTful API. Användning av PostgreSQL för lagring och hantering av databas.

**IoT**: Hårdvara baserad på Arduino med programmering i C++ och integrerade sensorer (PIR-sensor, mikrofon, luftkvalitetssensor). Anskaffad data kommuniceras via WiFi till backend.

## 4.2 Systemintegration

#### API-kommunikation:

Backend och IoT-komponenter samverkar via definierade API-endpoints.

Frontend gör kontinuerliga anrop mot API:et för att hämta aktuell bokningsstatus samt sensor- och händelsedata.

#### Databasintegration:

Data från IoT och användarinteraktioner loggas och lagras kontinuerligt.

Säkerhetsåtgärder såsom kryptering och roller implementeras för att skydda dataintegritet.

## 4.3 Interaktions- och Gränssnittskrav

#### Mobilapplikation:

Skalbar design med stöd för olika enheter (t.ex. mobiler och iPads).

Intuitiva visuella komponenter som tydligt markerar rumstillstånd (bokad, ledig, upptagen).

#### Dashboard för administratörer:

Ger översikt över all sensor-/bokningsdata.

Möjlighet att manuellt justera bokningar vid behov.

#### IoT-enheter:

Enkel installations- och konfigurationsprocess med medföljande dokumentation som beskriver installation, felsökning och underhåll.

# 5. Projektorganisation och Utvecklingsmetodik

## 5.1 Teamstruktur och Ansvarsområden

**Frontend** (FMWX24): Ansvarar för användargränssnittet, datavisualisering samt integration av API:er.

**IoT** (SUVX24): Utvecklar hårdvara samt firmware för sensorbaserad datainsamling och kommunikation.

**Backend** (FJSX24): Utvecklar API:er, hanterar databashantering och säkerhet samt utför datainsamling och lagring.

Varje team ansvarar för sin respektive dokumentation och rapporterar regelbundet vid gemensamma möten (t.ex. tisdagsmöten och standups). Teamledare för respektive subteam har det övergripande ansvaret för att synkronisera arbetet mellan grupperna.

## 5.2 Verktyg och Metodik

**Kodhantering**: GitHub

**Kommunikation**: Slack

**Sprintplanering**: GitHub Projects

**Mötesstruktur**: Regelbundna standups (minst en representant från varje team per möte), gemensamma arbetsmöten samt utvärderingsmöten (retrospektiv) under projektets gång.

# 6. Testning och Kvalitetssäkring

## 6.1 Teststrategi

**Enhetstester**: Varje funktionell modul, inklusive API-endpoints och IoT-komponenternas firmware, ska genomgå enhetstester.

**Integrationstester**: Testar kommunikation mellan frontend, backend samt IoT-enheter.

**Systemtester**: Sluttest för helhetssystemet för att verifiera alla användar- och systemkrav.

**Användartester**: Utförs med representanter från den primära målgruppen för att validera gränssnitt och användarvänlighet (WCAG-krav).

## 6.2 Kvalitetssäkring

**Dokumentation**: Uppdatering av README och API-dokumentation varje vecka, ansvar för denna tilldelas inom respektive team.

**Versionshantering**: Strikt användning av Git för spårning av kodändringar och att undvika merge-konflikter.

**Agila metoder**: Implementering av sprintar, standups och retrospektiv för att snabbt upptäcka och lösa problem samt hantera förändringar i projektplanen.

# 7. Riskanalys och Problemhantering

## 7.1 Identifierade Risker

**Kommunikationsbrist**: Risk för informationsluckor mellan teamen.

**Tekniska utmaningar**: Problem med integrationen mellan IoT-enheter, API och mobilapp.

**Tidsbrist**: Potentiellt uppkomna förseningar p.g.a. orealistiska deadlines eller olika arbetstempo.

**Versionshantering**: Risk för konflikter vid parallella utvecklingsinsatser.

## 7.2 Hanteringsplaner

**Regelbundna möten**: Veckovisa avstämningar där alla team är med. Avcheckning på Fredagar med Backend/SUVX

**Problemlösning**: Direkt kommunikation inom teamet vid uppkomst av blockerande problem, med eskalering till övriga team om behovet uppstår.

**Förändringshantering**: Vid behov av större ändringar, ska dessa synkroniseras och godkännas av beställaren enligt överenskommen process.

# 8. Tidsplan och Milstolpar

## 8.1 Huvudfaser

Vecka 10–11: Research, projektutvärdering och val av hårdvarulösningar.

Vecka 12: Utarbetande och inlämning av projektplan.

Vecka 13: Paus/planeringsfas.

Vecka 14: Start av arbetsmöte och påbörjan av utvecklingsarbete i teamen.

Vecka 15: Utveckling av API med mockad data (Fullstack-del).

Vecka 16: ~~Implementering av kärnfunktioner.~~

Vecka 17: ~~Leverans av MVP.~~

Vecka 18: Integration av databas och ersättning av mockad data.

Vecka 22: Testning, optimering samt implementering av säkerhetsfunktioner (JWT).

Vecka 23: Projektavslut med demo, utvärdering samt retrospektiv.

## 8.2 Hantering av Förseningar

Vid oförutsedda förseningar sker en omfördelning av resurser och en revidering av tidsplanen i enlighet med agila metoder. Större ändringar stäms av med gruppen innan de implementeras.

# 9. Leveranser och Dokumentationskrav

## 9.1 Systemleveranser

#### Backend:

API för datainsamling, hantering samt notifieringar.

Integration med JWT för säker autentisering och rollhantering.

PostgreSQL-databas för lagring och analys av bokningsdata.

#### Frontend:

Mobilapplikation byggd med React Native med ett WCAG-anpassat gränssnitt.

Ipad-layout för utomhusbokning.

Integration med backend-API:er för att visualisera aktuell data.

#### IoT:

Prototyp av kontrollenhet med Arduino och de angivna sensorerna.

Firmware i C++ för datainsamling och konvertering av sensorinformation.

Dokumentation som beskriver installation, användning och felsökning.

## 9.2 Dokumentation

Varje team ansvarar för att löpande uppdatera sin respektive dokumentation (README, API-dokumentation, användarmanualer).

Dokumentation ska vara tydligt strukturerad och tillgänglig för alla projektmedlemmar via gemensamma plattformar (GitHub, Slack).

# 10. Sammanfattning

Detta SRS-dokument sammanfattar de krav, tekniska lösningar och projektmetoder som ska tillämpas för att skapa det automatiserade bokningssystemet PAX. Genom att implementera automatiska bokningar baserade på realtidsdata från IoT-sensorer, ett användarvänligt gränssnitt och säkra backend-lösningar, syftar systemet till att effektivisera rumsutnyttjandet och möjliggöra kostnadsbesparingar för stora företag. Regelbunden kommunikation, tydliga teamroller och agila utvecklingsmetoder ligger till grund för projektets genomförande och framgång.

---

Detta SRS är avsett att vara levande och uppdateras kontinuerligt under projektets gång för att säkerställa att alla krav och förändringar dokumenteras och hanteras på ett strukturerat sätt.
