import React from "react";
import { NavigationContainer } from "@react-navigation/native";
import BottomTabNavigator from "./Navigation/BottomTabNavigator";
import { ThemeProvider } from "./theme/ThemeContext";
import { UserProvider } from "./context/UserContext";
import { AuthProvider } from "./context/AuthContext";

export default function App() {
  return (
    <ThemeProvider>
      <UserProvider>
        <AuthProvider>
          <NavigationContainer>
            <BottomTabNavigator />
          </NavigationContainer>
        </AuthProvider>
      </UserProvider>
    </ThemeProvider>
  );
}
