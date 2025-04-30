import React from 'react';
import { View, Text, TouchableOpacity, StyleSheet } from 'react-native';

export default function BookingButton({ onPress }) {
    return (
        <TouchableOpacity style={styles.container} onPress={onPress} activeOpacity={0.8}>
            <View style={styles.button}>
                <Text style={styles.text}>BOKA</Text>
            </View>
        </TouchableOpacity>
    );
}

const styles = StyleSheet.create({
    container: {
        top: -30,
        justifyContent: 'center',
        alignItems: 'center',
    },
    button: {
        width: 70,
        height: 70,
        borderRadius: 35,
        backgroundColor: '#7DBA6A',
        justifyContent: 'center',
        alignItems: 'center',
        shadowColor: '#000',
        shadowOpacity: 0.3,
        shadowOffset: { width: 0, height: 5 },
        shadowRadius: 5,
        elevation: 5,
    },
    text: {
        fontWeight: 'bold',
        color: '#000',
        fontSize: 14,
    },
});
