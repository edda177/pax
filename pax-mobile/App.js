import React from "react";
import { NavigationContainer } from "@react-navigation/native";
import BottomTabNavigator from "./Navigation/BottomTabNavigator";
import { ThemeProvider } from "./theme/ThemeContext";
import { UserProvider } from "./context/UserContext";
import { AuthProvider } from "./context/AuthContext";
import AuthNavigator from './Navigation/AuthNavigator'

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

function AppContent () {
  const { token, isLoading } = useAuth();
  if (isLoading) return null;

  return (
    <NavigationContainer>
    {token ? <BottomTabNavigator /> : <AuthNavigator />}
  </NavigationContainer>
  )
}
