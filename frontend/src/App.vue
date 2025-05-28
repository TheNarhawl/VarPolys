<template>
  <div class="container">
    <div class="input-section">
      <h2>Ввод полиномов</h2>
      <div class="polynomials-grid">
        <div
          class="polynomial"
          v-for="polyName in ['p1', 'p2']"
          :key="polyName"
        >
          <h3>{{ polyName.toUpperCase() }}</h3>
          <div
            v-for="(term, index) in polynomials[polyName]"
            :key="index"
            class="term"
          >
            <div class="term-controls">
              <input
                v-model.number="term.coefficient"
                type="number"
                placeholder="Coefficient"
                @input="calculate"
              />
              <button @click="removeTerm(polyName, index)" class="remove-btn">
                ×
              </button>
            </div>
            <div class="variables">
              <div
                v-for="(exp, var_name) in term.variables"
                :key="var_name"
                class="variable"
              >
                {{ var_name }}<sup>{{ exp }}</sup>
                <button
                  @click="removeVariable(polyName, index, var_name)"
                  class="remove-btn"
                >
                  ×
                </button>
              </div>
              <button @click="addVariable(polyName, index)" class="add-btn">
                + переменная
              </button>
            </div>
          </div>
          <button @click="addTerm(polyName)" class="add-btn">+ терм</button>
        </div>
      </div>
    </div>

    <div v-if="results" class="results-section">
      <h2>Результаты</h2>
      <div
        v-for="(storage, storageType) in results.terms"
        :key="storageType"
        class="storage-type"
      >
        <h3>{{ formatStorageType(storageType) }}</h3>

        <div class="polynomial-results-layout">
          <div class="polynomials-column">
            <div class="polynomial-view">
              <h4>Полином 1:</h4>
              <div class="terms">
                {{ formatTerms(results.terms[storageType].p1) }}
              </div>
            </div>
            <div class="polynomial-view">
              <h4>Полином 2:</h4>
              <div class="terms">
                {{ formatTerms(results.terms[storageType].p2) }}
              </div>
            </div>
          </div>
          <div class="operations-grid">
            <div class="operation">
              <h4>Сумма</h4>
              <div class="terms">
                {{ formatTerms(results.operations[storageType].sum) }}
              </div>
            </div>
            <div class="operation">
              <h4>Разность</h4>
              <div class="terms">
                {{ formatTerms(results.operations[storageType].difference) }}
              </div>
            </div>
            <div class="operation">
              <h4>Произведение</h4>
              <div class="terms">
                {{ formatTerms(results.operations[storageType].product) }}
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script setup>
import { ref, onMounted } from "vue";

const polynomials = ref({
  p1: [
    { coefficient: 3, variables: { x: 2, y: 1 } },
    { coefficient: 4, variables: { a: 1 } },
    { coefficient: -2, variables: { x: 1 } },
  ],
  p2: [
    { coefficient: -3, variables: { x: 2, y: 1 } },
    { coefficient: 5, variables: { a: 1 } },
    { coefficient: 2, variables: { x: 1 } },
  ],
});

const results = ref(null);

onMounted(() => {
  calculate();
});

const calculate = async () => {
  try {
    const response = await fetch("http://localhost:8080/process", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(polynomials.value),
    });
    results.value = await response.json();
  } catch (error) {
    console.error("Error:", error);
  }
};

const formatStorageType = (type) => {
  return type
    .split(/(?=[A-Z])/)
    .map((word) => word.charAt(0).toUpperCase() + word.slice(1))
    .join(" ");
};

const formatTerms = (terms) => {
  return terms
    .map((term) => {
      let result = term.coefficient;
      Object.entries(term.variables).forEach(([var_name, exp]) => {
        result += var_name;
        if (exp !== 1) result += `^${exp}`;
      });
      return result;
    })
    .join(" + ");
};

const addTerm = (polyName) => {
  polynomials.value[polyName].push({ coefficient: 0, variables: {} });
  calculate();
};

const removeTerm = (polyName, termIndex) => {
  polynomials.value[polyName].splice(termIndex, 1);
  calculate();
};

const addVariable = (polyName, termIndex) => {
  const varName = prompt("Введите переменную (например, x, y, z):");
  const exp = parseInt(prompt("Введите экспоненту:"));
  if (varName && !isNaN(exp)) {
    polynomials.value[polyName][termIndex].variables[varName] = exp;
    calculate();
  }
};

const removeVariable = (polyName, termIndex, varName) => {
  delete polynomials.value[polyName][termIndex].variables[varName];
  calculate();
};
</script>

<style>
@import url("https://fonts.googleapis.com/css2?family=Inter:wght@400;500;600;700&display=swap");
</style>

<style style="scss">
* {
  box-sizing: border-box;
  margin: 0;
  padding: 0;
}

body {
  font-family: "Inter", sans-serif;
  line-height: 1.5;
  color: #333;
  background-color: #f5f5f5;
}

.container {
  max-width: 1200px;
  margin: 0 auto;
  padding: 20px;
}

h1 {
  font-size: 24px;
  font-weight: 600;
  margin-bottom: 20px;
  color: #2c3e50;
  text-align: center;
}

h2 {
  font-size: 20px;
  font-weight: 600;
  margin-bottom: 15px;
  color: #2c3e50;
  border-bottom: 1px solid #eee;
  padding-bottom: 8px;
}

h3 {
  font-size: 18px;
  font-weight: 500;
  margin-bottom: 12px;
  color: #34495e;
}

h4 {
  font-size: 16px;
  font-weight: 500;
  margin-bottom: 8px;
  color: #7f8c8d;
}


.input-section,
.results-section {
  background: white;
  border-radius: 8px;
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.05);
  padding: 20px;
  margin-bottom: 20px;
}

.polynomials-grid {
  display: grid;
  grid-template-columns: 1fr 1fr;
  gap: 20px;
  margin-bottom: 20px;
}

.polynomial {
  border: 1px solid #e0e0e0;
  border-radius: 8px;
  padding: 15px;
  background: #fafafa;
}

.term {
  margin-bottom: 10px;
  padding: 10px;
  background: white;
  border-radius: 6px;
  border: 1px solid #eee;
}

.term-controls {
  display: flex;
  align-items: center;
  margin-bottom: 8px;
}

input {
  flex: 1;
  padding: 8px;
  border: 1px solid #ddd;
  border-radius: 4px;
  font-family: "Inter", sans-serif;
}

.variables {
  display: flex;
  flex-wrap: wrap;
  gap: 8px;
  align-items: center;
}

.variable {
  background: #e3f2fd;
  padding: 4px 8px;
  border-radius: 4px;
  display: flex;
  align-items: center;
  gap: 4px;
  font-size: 14px;
}

button {
  cursor: pointer;
  transition: all 0.2s;
}

.add-btn {
  background: #3498db;
  color: white;
  border: none;
  padding: 6px 12px;
  border-radius: 4px;
  font-size: 13px;
  margin-top: 5px;
}

.add-btn:hover {
  background: #2980b9;
}

.remove-btn {
  background: #e74c3c;
  color: white;
  border: none;
  width: 22px;
  height: 22px;
  border-radius: 50%;
  display: flex;
  align-items: center;
  justify-content: center;
  font-size: 12px;
  margin-left: 5px;
}

.remove-btn:hover {
  background: #c0392b;
}

.storage-type {
  margin-bottom: 25px;
  padding: 15px;
  background: #f8f9fa;
  border-radius: 8px;
  border-left: 4px solid #3498db;
}

.original-polynomials {
  display: grid;
  grid-template-columns: 1fr 1fr;
  gap: 15px;
  margin-bottom: 15px;
  padding-bottom: 15px;
  border-bottom: 1px dashed #ddd;
}

.polynomial-view {
  background: white;
  padding: 10px;
  border-radius: 6px;
  border: 1px solid #eee;
}

.operations-grid {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
  gap: 15px;
}

.operation {
  background: white;
  padding: 12px;
  border-radius: 6px;
  border: 1px solid #eee;
}

.terms {
  font-family: "Roboto Mono", monospace;
  font-size: 14px;
  color: #2c3e50;
  line-height: 1.6;
}

@media (max-width: 768px) {
  .polynomials-grid,
  .original-polynomials {
    grid-template-columns: 1fr;
  }
}
</style>
