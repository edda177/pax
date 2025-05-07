import React from "react";
import {
  View,
  Text,
  StyleSheet,
  SafeAreaView,
  StatusBar,
  Platform,
  Pressable,
} from "react-native";
import { MaterialCommunityIcons } from "@expo/vector-icons";
import { useTheme } from "../theme/ThemeContext";
import CardComponent from "../components/CardComponent";
import FormComponent from "../components/FormComponent";

const HomeScreen = () => {
  const { theme, isDark, toggleTheme } = useTheme();
  const styles = createStyles(theme);

  return (
    <SafeAreaView style={styles.safeArea}>
      <StatusBar
        barStyle={isDark ? "light-content" : "dark-content"}
        backgroundColor={theme.headerBackground}
      />
      <View style={styles.container}>
        <Pressable
          onPress={toggleTheme}
          accessible={true}
          accessibilityRole="button"
          accessibilityLabel={
            isDark ? "Byt till ljust tema" : "Byt till mörkt tema"
          }
          style={styles.toggleButton}
        >
          <MaterialCommunityIcons
            name={isDark ? "white-balance-sunny" : "weather-night"}
            size={30}
            color={theme.iconSwitchmode}
          />
        </Pressable>
        <CardComponent style={styles.CardComponentContainer} />
      </View>
    </SafeAreaView>
  );
};

const createStyles = (theme) =>
  StyleSheet.create({
    safeArea: {
      flex: 1,
      backgroundColor: theme.background,
      paddingTop: Platform.OS === "android" ? StatusBar.currentHeight : 0,
      paddingBottom: 0,
    },
    container: {
      flex: 1,
      backgroundColor: theme.background,
      justifyContent: "flex-start",
      alignItems: "center",
      paddingBottom: 0,
      paddingTop: 100,
    },
    text: {
      fontSize: 18,
      color: theme.text,
      marginBottom: 16,
    },
    toggleButton: {
      position: "absolute",
      top: 20,
      left: 20,
      zIndex: 1,
      backgroundColor: "#E3FAC825",
      borderRadius: 25,
      padding: 5,
    },
    CardComponentContainer: {
      top: 80,
      alignSelf: "center",
    },
  });

export default HomeScreen;
