import { StyleSheet, Text, View } from 'react-native'
import React from 'react'
import { useTheme } from '../theme/ThemeContext'

const CardComponent = ({ title, description }) => {
    const { theme } = useTheme();
    const styles = createStyles(theme);


    return (
            <View style={styles.card}>
                <Text style={styles.title}>Välkommen Namn!</Text>
                <Text style={styles.description}> Ditt bokade rum är... blabla </Text>
            </View>
    )
}

export default CardComponent

const createStyles = (theme) =>
    StyleSheet.create({
        card: {
            backgroundColor: theme.card,
            height: 217,
            width: 364,
            padding: 16,
            borderBottomRightRadius: 30,
            borderTopLeftRadius: 30,
            marginVertical: 8,
            elevation: 3,
        },
        title: {
            color: theme.textPrimary,
            fontFamily: "BadScript",
            fontSize: 26,
            fontWeight: 600,
            marginBottom: 8,
            letterSpacing: 0.5,
        },
        description: {
            color: theme.textSecondary,
            fontFamily: "NunitoSans",
            fontSize: 20,
            fontWeight: 500,
          },
    })

