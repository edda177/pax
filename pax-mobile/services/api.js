// const BASE_URL = "https://app.swaggerhub.com/apis-docs/alicegmn/pax-api/dev-oas3-new";

// export const loginWithApi = async (username, password) => {
//     try {
//         const response = await fetch(`${BASE_URL}`, {
//             method: "POST",
//             headers: { "Content-Type": "application/json", 
//                 'Accept' : 'application/json',
//             },
//             body: JSON.stringify({ 
//                 username: 'Anna',
//                 password: 'hejsanhoppsan' })
//         });

//         if (!response.ok) throw new Error("Inloggningen misslyckades");

//         return await response.json(); // Innehåller tokens
//     } catch(error) {
//         console.error("Login error", error);
//         return null;
//     }
// };


const BASE_URL = "https://virtserver.swaggerhub.com/alicegmn/pax-api/dev-oas3-new";

export const fetchUserProfile = async (token) => {
    try {
        const response = await fetch(`${BASE_URL}/dashboard`, {
            method: "GET",
            // headers: {
            //     Authorization: `Bearer ${token}`
            // }
        });

        if (!response.ok) throw new Error("Kunde inte hämta profil");

        return await response.json();
    } catch (error) {
        console.log("Fetch user error", error);
        return null;
    }
}

export const loginWithApi = async (username, password) => {
    try {
        const response = await fetch(`${BASE_URL}/auth/login`, {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ username, password })
        });
        if (!response.ok) throw new Error("Inloggningen misslyckades");
        // return await response.json(); // Innehåller tokens
        const data = await response.json();
        console.log(" JWT-token:", data.token); // logga token här (eller accessToken om det heter så)
        console.log(data);
        return data;
    } catch (error) {
        console.error("Login error", error);
        return null;
    }
};