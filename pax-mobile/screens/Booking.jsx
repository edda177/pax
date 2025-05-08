import React from "react";
import {
  View,
  StyleSheet,
  SafeAreaView,
  StatusBar,
  Platform,
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
      </View>

      <MapModal
        isVisible={isModalVisible}
        onClose={toggleModal}
        mapImage={require("../assets/maps/karta_pax-04.png")}
        imageDescription="Namnlista kommer snart :)"
      />
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
      paddingTop: 100,
    },
    toggleButtonContainer: {
      position: "absolute",
      top: 10,
      left: 10,
      zIndex: 1,
    },
  });

export default Booking;
