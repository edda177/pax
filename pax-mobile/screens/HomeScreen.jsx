import React from "react";
import {
  View,
  Text,
  StyleSheet,
  SafeAreaView,
  StatusBar,
  ScrollView,
  Platform,
  Pressable,
} from "react-native";
import { MaterialCommunityIcons } from "@expo/vector-icons"; // or "react-native-vector-icons/MaterialCommunityIcons"
import { useTheme } from "../theme/ThemeContext";
import CardComponent from "../components/CardComponent";

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
        <Text style={styles.text}>Welcome to the Home Screen!</Text>
        <Pressable
          onPress={toggleTheme}
          accessible={true}
          accessibilityRole="button"
          accessibilityLabel={isDark ? "Byt till ljust tema" : "Byt till mörkt tema"}
        >
        </Pressable>
        <CardComponent/>
      </View>
    </SafeAreaView>
  );
};

export default HomeScreen;

const createStyles = (theme) =>
  StyleSheet.create({
    safeArea: {
      flex: 1,
      backgroundColor: theme.background,
      paddingTop: Platform.OS === "android" ? StatusBar.currentHeight : 0,
    },
    container: {
      flex: 1,
      backgroundColor: theme.background,
      paddingBottom: 150,
      justifyContent: "center",
      alignItems: "center",
    },
    text: {
      fontSize: 18,
      color: theme.text,
      marginBottom: 16,
    },
  });
