// components/ThemeToggleTabButton.js
import React from "react";
import { Pressable } from "react-native";
import { MaterialCommunityIcons } from "@expo/vector-icons";
import { useTheme } from "../theme/ThemeContext";

const ThemeToggleTabButton = ({ onPress, accessibilityState }) => {
    const { isDark, toggleTheme, theme } = useTheme();
    const focused = accessibilityState?.selected;

    return (
        <Pressable
            onPress={toggleTheme}
            style={{
                flex: 1,
                justifyContent: "center",
                alignItems: "center",
            }}
            accessibilityRole="button"
            accessibilityLabel={isDark ? "Byt till ljust tema" : "Byt till mörkt tema"}
        >
            <MaterialCommunityIcons
                name={isDark ? "white-balance-sunny" : "weather-night"}
                color={focused ? theme.accent : "gray"}
                size={24}
            />
        </Pressable>
    );
};

export default ThemeToggleTabButton;
