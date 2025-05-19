import { StyleSheet, Text, View, Animated, Platform } from "react-native";
import React, { useEffect, useRef } from "react";
import { useTheme } from "../theme/ThemeContext";
import AnimatedLogo from "../components/AnimatedLogo";

const LoadingScreen = () => {
  const { theme, isDark, toggleTheme } = useTheme();
  const styles = createStyles(theme);

  const scaleAnimated = useRef(new Animated.Value(0.4)).current;
  const opacityAnimated = useRef(new Animated.Value(0.9)).current;


  useEffect(() => {
    const timeout = setTimeout(() => {
      //Funktion aniering
      //Start två samtidigt
      Animated.parallel([
        Animated.timing(scaleAnimated, {
          toValue: 1,
          duration: 800,
          useNativeDriver: Platform.OS !== "web",
        }),
        Animated.timing(opacityAnimated, {
          toValue: 0.2,
          duration: 800,
          useNativeDriver: Platform.OS !== "web",
        }),
      ]).start();
    }, 1100);

    return () => clearTimeout(timeout);
  }, []);

  return (
    <View style={styles.container}>
      <AnimatedLogo
        style={{
          transform: [{ scale: scaleAnimated }],
          opacity: opacityAnimated,
        }}
      />
      <Text style={styles.text}> vänta lite..</Text>
    </View>
  );
};

export default LoadingScreen;

// styles längst ned men backgroundColor hämtas inline (theme)
const createStyles = (theme) =>
  StyleSheet.create({
    container: {
      flex: 1,
      backgroundColor: "#061a17",
      paddingBottom: 150,
      alignItems: "center",
      justifyContent: "center",
      flexDirection: "column",
      paddingTop: "30vh",
    },
    text: {
      flex: 1,
      alignItems: "center",
      fontFamily: "NunitoSans",
      justifyContent: "center",
      flexDirection: "column",
      color: "rgb(216, 250, 176)",
      fontSize: "0.8rem",
      letterSpacing: "0.25rem",
      fontWeight: "500",
      textAlign: "right",
      paddingTop: "2vh",
      textTransform: "uppercase",
    },
  });
