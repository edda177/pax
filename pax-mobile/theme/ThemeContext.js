import React, { createContext, useContext, useState } from "react";
import { darkTheme, lightTheme } from "./colors";
import { buildCustomTheme } from "./customTheme";
import { useFonts} from 'expo-font';
import { Text, View} from 'react-native'

const ThemeContext = createContext();

export const ThemeProvider = ({ children }) => {
  const [isDark, setIsDark] = useState(true);
  const theme = isDark ? darkTheme : lightTheme;
  const customTheme = buildCustomTheme(theme, isDark);
  const toggleTheme = () => setIsDark((prev) => !prev);

  const [fontsLoaded] = useFonts({
    "BadScript": require("../assets/fonts/BadScript-Regular.ttf"),
    "NunitoSans": require('../assets/fonts/NunitoSans.ttf'),
    "Nunito": require('../assets/fonts/Nunito-VariableFont_wght.ttf'),
  });

  if (!fontsLoaded) {
    return (
      <View>
        {" "}
        <Text>Laddar typsnitt..</Text>{" "}
      </View>
    );
  }

  return (
    <ThemeContext.Provider value={{ isDark, theme, toggleTheme, customTheme }}>
      {children}
    </ThemeContext.Provider>
  );
};

export const useTheme = () => useContext(ThemeContext);







//   const theme = isDark ? darkTheme : lightTheme;
//   const customTheme = buildCustomeTheme(theme, isDark);

//   const toggleTheme = () => setIsDark((prev) => !prev);

//   return (
//     <ThemeContext.Provider value={{ isDark, theme, toggleTheme, customTheme }}>
//       {children}
//     </ThemeContext.Provider>
//   );
// };

// export const useTheme = () => useContext(ThemeContext);
