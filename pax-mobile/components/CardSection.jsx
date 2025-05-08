import { StyleSheet, Text, View, ScrollView } from 'react-native'
import React from 'react'
import CardComponent from './CardComponent'


const CardSection = ({ horizontal = false }) => {
    
    return (
        <View style={styles.section}>
            <ScrollView
            horizontal={horizontal}
            showsHorizontalScrollIndicator={false}
            contentContainerStyle={[
                styles.scrollContent, 
                horizontal && styles.horizontalContent
            ]}
            >
                <CardComponent
                    title="WishLists"
                    description="hjejekjdskfjgjvjj hsfjh jfsdghhfh"
                />
                <CardComponent
                    title="Kvällsyoga"
                    description="Avsluta dagen med ett lugnt yogapass"
                />
                <CardComponent
                    title="Kvällsyoga"
                    description="Avsluta dagen med ett lugnt yogapass"
                />
            </ScrollView>

        </View>
    )
}

export default CardSection

const styles = StyleSheet.create({
    section: {
        flex: 1
    },
    scrollContent: {
        paddingVertical: 10,
        alignItems: "center"   
    },
    horizontalContent: {
        flexDirection: "row"
    }
})