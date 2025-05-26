import React from "react";
import { View, Text, Image, StyleSheet } from "react-native";
import { useTheme } from "../theme/ThemeContext";

const Contact = () => {
  const { theme, isDark, toggleTheme } = useTheme();
  const styles = createStyles(theme);

  return (
    <View style={styles.container}>
      <Image
        source={require("../assets/illustrationer/illustrationer_pax-01.svg")}
        style={styles.image}
        resizeMode="cover"
      />
      <Text style={styles.textFet}>Contact us:</Text>
      <Text style={styles.text}>
        +46(0) 771-729 729 <br /> +46 (0) 771-PAX PAX
      </Text>
    </View>
  );
};

export default Contact;

const createStyles = (theme) =>
  StyleSheet.create({
    container: {
      flex: 1,
      backgroundColor: theme.background,
      // width: "100vw",
      // minHeight: "100vh",
      flexDirection: "column",
      justifyContent: "center",
      alignItems: "center",
    },
    text: {
      color: theme.textPrimary,
      fontSize: 18,
      fontWeight: "400",
      textAlign: "center",
      textTransform: "uppercase",
      lineHeight: 30,
      letterSpacing: 0.6,
    },
    textFet: {
      color: theme.textPrimary,
      fontFamily: "Nunito",
      fontSize: 18,
      fontWeight: "800",
      textAlign: "center",
      textTransform: "uppercase",
      lineHeight: 30,
      letterSpacing: 0.6,
    },
    image: {
      // width: "90vw",
      // height: "35vh",
    },
  });
