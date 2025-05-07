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
        <Text style={styles.bookingtext}>Boka ett rum</Text>

        {/* Allt innehåll under rubriken */}
        <View style={styles.cardWrapper}>
          <View style={styles.card}>
            <Text style={styles.title}>Lediga rum:</Text>
          </View>

          <Pressable style={styles.pressableButton}>
            <Text style={styles.pressableText}>Kartöversikt</Text>
          </Pressable>

          <View style={styles.card2}>
            <Text style={styles.title}>Favoritrum:</Text>
          </View>
        </View>
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
      fontWeight: "600",
      marginBottom: 8,
      letterSpacing: 0.5,
      textTransform: "uppercase",
    },
    cardWrapper: {
      width: "100%",
      alignItems: "center",
      marginTop: 16,
    },
    card: {
      backgroundColor: theme.card,
      height: 217,
      width: "90%",
      padding: 16,
      borderBottomRightRadius: 30,
      borderTopLeftRadius: 30,
      marginVertical: 12,
      elevation: 3,
    },
    card2: {
      backgroundColor: theme.card,
      height: 217,
      width: "90%",
      padding: 16,
      borderBottomRightRadius: 30,
      borderTopLeftRadius: 30,
      marginVertical: 12,
      elevation: 3,
    },
    title: {
      color: theme.textSecondary,
      fontFamily: "Nunito",
      fontSize: 20,
      fontWeight: "500",
    },
    pressableButton: {
      backgroundColor: theme.primary,
      width: "90%",
      height: 60,
      justifyContent: "center",
      alignItems: "center",
      borderRadius: 30,
      marginVertical: 12,
      elevation: 3,
    },
    pressableText: {
      color: theme.textOnPrimary,
      fontFamily: "Nunito",
      fontSize: 18,
      fontWeight: "600",
      textTransform: "uppercase",
    },
  });

export default Booking;
