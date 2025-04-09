import React, { createContext, useContext, useState } from "react";
import { darkTheme, lightTheme } from "./colors";
import { buildCustomeTheme } from "./customTheme";

const ThemeContext = createContext();

export const ThemeProvider = ({ children }) => {
  const [isDark, setIsDark] = useState(false);

  const theme = isDark ? darkTheme : lightTheme;
  const customTheme = buildCustomeTheme(theme, isDark);

  const toggleTheme = () => setIsDark((prev) => !prev);

  return (
    <ThemeContext.Provider value={{ isDark, theme, toggleTheme, customTheme }}>
      {children}
    </ThemeContext.Provider>
  );
};

export const useTheme = () => useContext(ThemeContext);
