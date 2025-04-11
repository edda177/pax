FROM node:16
WORKDIR /usr/src/app
# Kopiera package.json först (för cache)
COPY package*.json ./
# Installera beroenden
RUN npm install
# Installera nodemon globalt
RUN npm install -g nodemon
# Kopiera resten av koden
COPY . .
EXPOSE 13000
CMD ["nodemon", "src/index.js"]