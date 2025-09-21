import { useState } from 'react'
import reactLogo from './assets/react.svg'
import viteLogo from '/vite.svg'
import axios from "axios"
import './App.css'

function App() {
  const [myText, setMyText] = useState("");

  return (
    <>
      <div>
        <a href="https://vite.dev" target="_blank">
          <img src={viteLogo} className="logo" alt="Vite logo" />
        </a>
        <a href="https://react.dev" target="_blank">
          <img src={reactLogo} className="logo react" alt="React logo" />
        </a>
      </div>
      <h1>Vite + React</h1>
      <div className="card">
        <button onClick={async () => {
          const res = await axios.post("http://127.0.0.1:3000/api", {
            "username": "test",
            "password": "123456",
          })
          setMyText(JSON.stringify(res.data, null, 2));       
        }}>
          Click here!
        </button>
        {myText && (<>
          <h1>Result:</h1>
          <p>{myText}</p>
        </>)}
      </div>
      <p className="read-the-docs">
        Click on the Vite and React logos to learn more
      </p>
    </>
  )
}

export default App
