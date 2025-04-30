import { StyleSheet, Text, View } from 'react-native'
import React from 'react'
import { useTheme } from '../theme/ThemeContext'

const CardComponent = ({ title, description }) => {
    const { theme } = useTheme();
    const styles = createStyles(theme);


    return (
            <View style={styles.card}>
                <Text style={styles.title}>{title}</Text>
                <Text style={styles.description}>{description} </Text>
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
            fontSize: 18,
            fontWeight: 'bold',
            marginBottom: 8,
        },
        description: {
            color: theme.textSecondary,
            fontSize: 14,
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