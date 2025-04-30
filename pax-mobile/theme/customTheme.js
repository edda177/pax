export const buildCustomTheme = (baseTheme, isDark) => ({
    dark: isDark,
    colors: {
      background: baseTheme.background,
      card: baseTheme.card,
      textLight: baseTheme.textLight,
      textDark: baseTheme.textDark,
      textPrimary: baseTheme.textPrimary,
      primary: baseTheme.primary,
      secondary: baseTheme.secondary,
      accent: baseTheme.accent,
      tabBar: baseTheme.tabBackground,
    },
    fonts: {
      regular: { fontFamily: "System", fontWeight: "normal" },
      medium: { fontFamily: "System", fontWeight: "500" },
    },
    fontFamily: "BadScript-Regular", 
  });