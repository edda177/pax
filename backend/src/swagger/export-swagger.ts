import * as fs from "fs";
import * as path from "path";
import swaggerSpec from "./swagger";

const outputPath = path.join(__dirname, "../../swagger-export.json");

fs.writeFileSync(outputPath, JSON.stringify(swaggerSpec, null, 2));
console.log("✅ Swagger JSON exported to", outputPath);
