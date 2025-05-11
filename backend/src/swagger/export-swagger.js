"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
// export-swagger.ts
var fs_1 = require("fs");
var swagger_1 = require("./swagger");
fs_1.default.writeFileSync("swagger-export.json", JSON.stringify(swagger_1.default, null, 2));
console.log("Swagger JSON exported to swagger-export.json");
