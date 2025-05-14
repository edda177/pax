import { ScrollView, StyleSheet, Text, View } from 'react-native'
import React from 'react'
import FormComponent from '../components/FormComponent'
import LogoComponent from '../components/LogoComponent'
import { useTheme } from '../theme/ThemeContext';
import ThemeToggleTabButton from '../components/ThemeToggleTabButton';
import ButtonComponent from '../components/buttons/ButtonComponent';

const LoginTest = () => {
      const { theme } = useTheme ();
      const styles = createStyles (theme);
  return (
    <ScrollView>
    <View style={styles.container}>
     <ThemeToggleTabButton /> 
     <LogoComponent style={styles.logo} />
     <FormComponent />
     <ButtonComponent 
     style={styles.button}/>
    </View>
    </ScrollView>
  )
}

export default LoginTest

const createStyles = (theme) => 
    StyleSheet.create({
      container: {
        flex: 1,
        backgroundColor: theme.background,
        paddingBottom: 0,
      },
      logo: {
        marginTop: 80,
        alignSelf: 'center',

      },
      label: {
        fontSize: 20,
        textAlign: 'left',
        alignSelf: 'flex-start',
        marginLeft: 10,
        color: theme.textPrimary,

      },
      input: {
        padding: 20,
        width: 300,
        backgroundColor: theme.card,
        borderRadius: 10,
        margin: 10,
      },
      button: {
        padding: 15,
        backgroundColor: theme.card,
        borderRadius: 10,
        width: 140,
        textAlign: 'right',
        alignSelf: 'flex-end',
      },
      pressed: {
      },
    })