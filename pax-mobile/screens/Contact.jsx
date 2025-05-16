import React from 'react';
import { View, Text, StyleSheet } from 'react-native';
import { useTheme } from '../theme/ThemeContext';

const Contact = () => {
  const { theme, isDark, toggleTheme } = useTheme();
  const styles = createStyles (theme);

  return (
      <View style={styles.container}>
 <Text style={styles.text}>
    Contact us: +46(0) 771-729 729 (0771-PAX PAX)
    </Text>
     </View>
  )
};

export default Contact;

const createStyles = (theme) => 
    StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: theme.background,
    width: "100vw",
    minHeight: "100vh",
    flexDirection: "column",
    justifyContent: "center",
    alignItems: "center",
  },
  text: { 
    color: theme.textPrimary,
    fontSize: 18, 
    fontWeight: "600", 
    textAlign: "center",
    textTransform: "uppercase",
    letterSpacing: 0.6
  },
});
