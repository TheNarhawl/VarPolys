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
          <div class="polynomials-column-vertical">
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
          <div class="operations-row-horizontal">
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

<style style="scss">
@import url("https://fonts.googleapis.com/css2?family=Inter:wght@400;500;600;700&display=swap");

* {
  box-sizing: border-box;
  margin: 0;
  padding: 0;
}

body {
  font-family: "Inter", sans-serif;
  background-color: #f5f5f5;
  color: #333;
}

.container {
  max-width: 1200px;
  margin: 0 auto;
  padding: 10px;
}

h1 {
  font-size: 20px;
  font-weight: 600;
  margin-bottom: 15px;
  text-align: center;
  color: #2c3e50;
}

h2 {
  font-size: 18px;
  font-weight: 600;
  margin-bottom: 10px;
  color: #2c3e50;
  border-bottom: 1px solid #eee;
  padding-bottom: 5px;
}

h3 {
  font-size: 16px;
  font-weight: 500;
  margin-bottom: 8px;
  color: #34495e;
}

h4 {
  font-size: 14px;
  font-weight: 500;
  margin-bottom: 5px;
  color: #7f8c8d;
}

.input-section,
.results-section {
  background: #fff;
  border-radius: 6px;
  box-shadow: 0 1px 3px rgba(0, 0, 0, 0.05);
  padding: 15px;
  margin-bottom: 15px;
}

.polynomials-grid {
  display: flex;
  gap: 10px;
  margin-bottom: 15px;
}

.polynomial {
  flex: 1;
  border: 1px solid #e0e0e0;
  border-radius: 6px;
  padding: 10px;
  background: #fafafa;
}

.term {
  margin-bottom: 8px;
  padding: 8px;
  background: #fff;
  border-radius: 4px;
  border: 1px solid #eee;
}

.term-controls {
  display: flex;
  align-items: center;
  margin-bottom: 6px;
}

input {
  flex: 1;
  padding: 6px;
  border: 1px solid #ddd;
  border-radius: 4px;
  font-family: "Inter", sans-serif;
  font-size: 13px;
}

.variables {
  display: flex;
  flex-wrap: wrap;
  gap: 6px;
  align-items: center;
}

.variable {
  background: #e3f2fd;
  padding: 3px 6px;
  border-radius: 3px;
  display: flex;
  align-items: center;
  gap: 3px;
  font-size: 13px;
}

button {
  cursor: pointer;
  transition: background 0.2s, color 0.2s, transform 0.1s;
  font-family: "Inter", sans-serif;
  font-size: 14px;
  border: none;
  border-radius: 6px;
  padding: 6px 12px;
  background-color: #ecf0f1;
  color: #2c3e50;
}

button:hover {
  background-color: #d0d7dc;
  transform: translateY(-1px);
}

.add-btn {
  background-color: #3498db;
  color: white;
  font-weight: 500;
  padding: 6px 14px;
  border-radius: 6px;
  margin-top: 6px;
}

.add-btn:hover {
  background-color: #2980b9;
}

.remove-btn {
  background-color: #f0f0f0;
  color: #c0392b;
  width: 26px;
  height: 26px;
  border-radius: 50%;
  display: flex;
  align-items: center;
  justify-content: center;
  font-size: 16px;
  padding: 0;
  margin-left: 6px;
  border: 1px solid #e0e0e0;
}

.remove-btn:hover {
  background-color: #ffecec;
  color: #e74c3c;
}

.storage-type {
  margin-bottom: 20px;
  padding: 12px;
  background: #f8f9fa;
  border-radius: 6px;
  border-left: 3px solid #3498db;
}

.polynomial-results-layout {
  display: flex;
  gap: 15px;
  margin-top: 10px;
}

.polynomials-column-vertical {
  display: flex;
  flex-direction: column;
  gap: 10px;
  flex: 1;
}

.operations-row-horizontal {
  display: flex;
  flex-direction: row;
  gap: 10px;
  flex: 2;
}

.operations-row-horizontal .operation {
  flex: 1;
}

.polynomials-column {
  flex: 1;
  min-width: 250px;
  display: flex;
  flex-direction: column;
  gap: 10px;
}

.polynomial-view {
  background: white;
  padding: 8px;
  border-radius: 4px;
  border: 1px solid #eee;
}

/*
.operations-grid {
  flex: 1;
  min-width: 250px;
  display: flex;
  flex-direction: column;
  gap: 10px;
}
*/

.operation {
  background: white;
  padding: 8px;
  border-radius: 4px;
  border: 1px solid #eee;
}

.terms {
  font-family: "Roboto Mono", monospace;
  font-size: 13px;
  line-height: 1.4;
  color: #2c3e50;
}

@media (max-width: 768px) {
  .polynomials-grid,
  .polynomial-results-layout {
    flex-direction: column;
  }
}
</style>
