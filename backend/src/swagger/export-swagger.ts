import * as fs from "fs";
import * as path from "path";
import { fileURLToPath } from "url";
import swaggerSpec from "./swagger";

// Get current file path (needed for ES modules)
const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

// Export Swagger spec to JSON
const outputPath = path.join(__dirname, "../../swagger-export.json");

fs.writeFileSync(outputPath, JSON.stringify(swaggerSpec, null, 2));
console.log("✅ Swagger JSON exported to", outputPath);
