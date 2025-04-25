import { createRoot } from "react-dom/client";
import "./index.css";
import App from "./App";
import { BrowserRouter, Routes, Route } from "react-router-dom";
import Auth from "./pages/Auth";
import Stats from "./pages/Stats";
import Users from "./pages/Users";
import Navbar from "./components/Navbar";
const rootElement = document.getElementById("root");

if (!rootElement) {
  throw new Error("Root element not found");
}

createRoot(rootElement).render(
  <BrowserRouter>
    <Navbar />
    <Routes>
      <Route path="/" element={<App />} />
      <Route path="/auth" element={<Auth />} />
      <Route path="/stats" element={<Stats />} />
      <Route path="/users" element={<Users />} />
    </Routes>
  </BrowserRouter>
);
