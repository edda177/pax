import { StyleSheet, Text, View, Image } from 'react-native'
import React from 'react'

const LogoComponent = () => {
  return (
    <View>
      <Image source={require('../assets/logo/pax_logo-18.png')}></Image>
    </View>
  )
}

export default LogoComponent

const styles = StyleSheet.create({})