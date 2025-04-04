const express = require("express");
const dotenv = require("dotenv");
const exampleRoutes = require("./routes/example");

dotenv.config();

const app = express();
const port = process.env.PORT || 3000;

app.use(express.json()); // for parsing application/json

// Example route
app.use("/example", exampleRoutes);

app.get("/", (req, res) => {
  res.send("Hello World!");
});

app.listen(port, () => {
  console.log(`Server listening on port ${port}`);
});

module.exports = app; // Export for testing
