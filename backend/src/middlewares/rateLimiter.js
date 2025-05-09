import rateLimit from 'express-rate-limit';


const limiter = rateLimit({
    windowMs: 10 * 60 * 1000, // 15 minuter
    max: 100, // Tillåt 100 förfrågningar per IP inom 15 minuter
    message: "Too many requests, please try again later.",
    handler: (req, res) => {
        // Loggar om rate-limit överstiger 100 förfrågningar
        console.log(`[RATE LIMIT] ${req.ip} exceeded the limit of 100 requests in 15 minutes.`);
        res.status(429).send("Too many requests, please try again later.");
    },
});


export default limiter;
