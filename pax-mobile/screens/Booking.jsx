import React from "react";
import {
  View,
  StyleSheet,
  SafeAreaView,
  StatusBar,
  Platform,
  Text,
  Pressable,
} from "react-native";
import { useTheme } from "../theme/ThemeContext";
import ThemeToggleTabButton from "../components/ThemeToggleTabButton";

const Booking = () => {
  const { theme, isDark } = useTheme();
  const styles = createStyles(theme);

  return (
    <SafeAreaView style={styles.safeArea}>
      <StatusBar
        barStyle={isDark ? "light-content" : "dark-content"}
        backgroundColor={theme.headerBackground}
      />
      <View style={styles.container}>
        <View style={styles.toggleButtonContainer}>
          <ThemeToggleTabButton />
        </View>
        <Text style={styles.bookingtext}>Boka ett rum </Text>
      </View>
      <View style={styles.card}>
        <Text style={styles.title}>Lediga rum:</Text>
      </View>
      <Pressable>hej</Pressable>
      <View style={styles.card2}>
        <Text style={styles.title}>Favoritrum:</Text>
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
    },
    container: {
      flex: 1,
      backgroundColor: theme.background,
      justifyContent: "flex-start",
      alignItems: "center",
      paddingTop: 80,
    },
    toggleButtonContainer: {
      position: "absolute",
      top: 10,
      left: 10,
      zIndex: 1,
    },
    bookingtext: {
      color: theme.textPrimary,
      fontFamily: "Nunito",
      fontSize: 30,
      fontWeight: 600,
      marginBottom: 8,
      letterSpacing: 0.5,
      textTransform: "uppercase",
    },
    card: {
      backgroundColor: theme.card,
      height: 217,
      width: 364,
      padding: 16,
      borderBottomRightRadius: 30,
      borderTopLeftRadius: 30,
      marginVertical: 8,
      elevation: 3,
      alignSelf: "center",
      position: "absolute",
      top: 125,
    },
    card2: {
      backgroundColor: theme.card,
      height: 217,
      width: 364,
      padding: 16,
      borderBottomRightRadius: 30,
      borderTopLeftRadius: 30,
      marginVertical: 8,
      elevation: 3,
      alignSelf: "center",
      position: "absolute",
      bottom: 190,
    },
    title: {
      color: theme.textSecondary,
      fontFamily: "Nunito",
      fontSize: 20,
      fontWeight: 500,
    },
  });

export default Booking;
