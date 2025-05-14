import { StyleSheet, Text, View, Animated, Platform } from "react-native";
import React, { useEffect, useRef } from "react";
import { useTheme } from "../theme/ThemeContext";
import AnimeradLogo from "../components/AnimeradLogo";

const LogoScreen = () => {
  const { theme, isDark, toggleTheme } = useTheme();
  const styles = createStyles(theme);

  const scaleAnimated = useRef(new Animated.Value(0.5)).current;
  const opacityAnimated = useRef(new Animated.Value(0.2)).current;

  useEffect(() => {
    const timeout = setTimeout(() => {
      //Funtion aniering
      //Start två samtidigt
      Animated.parallel([
        Animated.timing(scaleAnimated, {
          toValue: 1,
          duration: 500,
          useNativeDriver: Platform.OS !== "web",
        }),
        Animated.timing(opacityAnimated, {
          toValue: 1,
          duration: 500,
          useNativeDriver: Platform.OS !== "web",
        }),
      ]).start();
    }, 800);

    return () => clearTimeout(timeout);
  }, []);

  return (
    <View style={styles.container}>
      <AnimeradLogo
        style={{
          transform: [{ scale: scaleAnimated }],
          opacity: opacityAnimated,
        }}
      />
      <Text style={styles.text}> välkommen</Text>
    </View>
  );
};

export default LogoScreen;

// styles längst ned men backgroundColor hämtas inline (theme)
const createStyles = () =>
  StyleSheet.create({
    container: {
      flex: 1,
      backgroundColor: "#061a17",
      paddingBottom: 150,
      alignItems: "center",
      justifyContent: "center",
      flexDirection: "column",
      paddingTop: "20%",
    },
    text: {
      flex: 1,
      alignItems: "center",
      justifyContent: "center",
      flexDirection: "column",
      color: "#f6f8c4",
      fontSize: 1.3,
      fontWeight: 100,
      textAlign: "center",
      paddingTop: "10%",
      textTransform: "uppercase",
      letterSpacing: 1.4,
    },
  });
