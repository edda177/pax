const BASE_URL = "https://paxdb.vercel.app";

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

export const loginWithApi = async (email, password) => {
    try {
        const response = await fetch(`${BASE_URL}/auth/login`, {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ email, password })
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