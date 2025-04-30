import React from "react";
import { Pressable, Text, View } from "react-native";
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
                paddingVertical: 8,
            }}
            accessibilityRole="button"
            accessibilityLabel={isDark ? "Byt till ljust tema" : "Byt till mörkt tema"}
        >
            <View style={{ alignItems: "center" }}>
                <MaterialCommunityIcons
                    name={isDark ? "white-balance-sunny" : "weather-night"}
                    color={focused ? theme.accent : "gray"}
                    size={24}
                />
                <Text
                    style={{
                        color: focused ? theme.accent : "gray",
                        marginTop: 4,
                        fontSize: 14,
                        fontFamily: "Arial",
                        fontWeight: "400",
                        textAlign: "center",
                    }}
                >
                    {isDark ? "Dark" : "Light"}
                </Text>
            </View>
        </Pressable>
    );
};

export default ThemeToggleTabButton;
