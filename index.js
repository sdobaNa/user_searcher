import open from 'open'
import express from 'express'
import bindings from "bindings"

const app = express()
const validate_user = bindings('validate_user')

app.set('view engine', 'ejs')
app.use(express.urlencoded({ extended: false}))

app.get('/', (req, res) => {
    res.render("MainPage")
})

app.post('/check-user', (req, res) => {
    try{
    var isUser = validate_user.ValidateUser(req.body.username)
    res.render('ResponsePage', {
        username: req.body.username,
        isUser: isUser
    })
    } catch(err) {
        console.log(err)
        res.render('MainPage')
    }
})

app.listen(3000, function () {
    console.log('Server listen http://localhost:3000')
  })

open('http://localhost:3000')
  