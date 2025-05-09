import { StyleSheet, Text, View } from 'react-native'
import React from 'react'
import { useTheme } from '../theme/ThemeContext'

const CardComponent = ({ title, description }) => {
    const { theme } = useTheme();
    const styles = createStyles(theme);


    return (
            <View style={styles.card}>
                <Text style={styles.title}>Välkommen Namn!</Text>
                <Text style={styles.description}> Ditt bokade rum är ledigt om ca. 3 min. Ditt rum är "PAX1"på våning 4. Ha en bra dag! </Text>
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

// const styles = StyleSheet.create({
//     card: {
//         borderRadius: 12,
//         padding: 20, 
//         width: 260,
//         height: 160, 
//         marginBottom: 14,
//         marginHorizontal: 14

//     }
// })